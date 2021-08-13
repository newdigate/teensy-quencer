//
// Created by Nicholas Newdigate on 29/06/2020.
//

#ifndef TEENSYSEQUENCER_SEQUENCER_H
#define TEENSYSEQUENCER_SEQUENCER_H
#include <Arduino.h>
#include "tempo.h"
#include "songposition.h"
#include "looptype.h"

#include <set>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

namespace newdigate { 

    struct sequencerevent {
        uint8_t channel = 0;
        uint8_t noteNumber = 0;
        unsigned char velocity = 0;
        long position = 0;
        bool isNoteStartEvent = true;
        unsigned char status  = 0;

        bool operator ()(sequencerevent *lhs, const sequencerevent *rhs) const
        {
            return lhs->position < rhs->position;
        }
    };

    struct pattern {
        unsigned _loop_duration_bars = 0;
        vector <sequencerevent*> _sorted_events;

        void addelement(unsigned startTick, unsigned length, uint8_t channel, uint8_t noteNumber) {
            sequencerevent *start = new sequencerevent();
            start->channel = channel;
            start->position = startTick;
            start->isNoteStartEvent = true;
            start->noteNumber = noteNumber;
            _sorted_events.push_back(start);

            sequencerevent *end = new sequencerevent();
            end->channel = channel;
            end->position = startTick + length;
            end->isNoteStartEvent = false;
            end->noteNumber = noteNumber;
            _sorted_events.push_back(end);
        }

        void addevent(sequencerevent *event) {
            _sorted_events.push_back( event );
        }

        // this method needs to be called if notes are not added in order
        void sortEvents(unsigned pattern) {
            multiset<sequencerevent*, sequencerevent> eventsForPattern;
            eventsForPattern.insert(_sorted_events.begin(), _sorted_events.end());

            _sorted_events.clear();
            for(auto &&event:eventsForPattern) {
                _sorted_events.push_back(event);
            }
        }

    };

    struct sequencertempoevent : sequencerevent {
        double tempo = 0.0;
    };

    class sequencer {
    public:
        sequencer(tempo &tempo, songposition *position) : _patterns(0), _tempo(tempo), _position(position) {}
        ~sequencer() {
            for(auto &&pat : _patterns) {
                delete pat;
            }
        }

        void tick(unsigned long micros) {
            if (!_playing) return;
            _microseconds = micros;

            unsigned long deltaMicros = _microseconds - _lastTickMicroseconds;
            if (deltaMicros >= _tempo._microseconds_per_tick) {
                _lastTickMicroseconds = _microseconds;

                unsigned long deltaTicks = deltaMicros / _tempo._microseconds_per_tick;
                _position->totalTicks += deltaTicks;
                _position->ticks += deltaTicks;
                if (_position->ticks >= 480) {
                    _position->beat += _position->ticks / 480;
                    _position->ticks %= 480;
                }
                if (_position->beat > 4) {
                    _position->bar += _position->beat / 4;
                    _position->beat %= 4;
                }

                unsigned long totalTicks = _position->totalTicks;
                bool wrapped = false;
                if (_position->bar > _patterns[_currentPattern]->_loop_duration_bars) {
                    _position->bar %= _patterns[_currentPattern]->_loop_duration_bars;
                    _position->ticks %= 480 * 4 *  _patterns[_currentPattern]->_loop_duration_bars;
                    _position->totalTicks %= 480 * 4 * _patterns[_currentPattern]->_loop_duration_bars;
                    wrapped = true;
                }
            
                vector<sequencerevent*> &sortedEventsForPattern = _patterns[_currentPattern]->_sorted_events;
                while (_last_event_index < sortedEventsForPattern.size() ) {
                    sequencerevent* c = sortedEventsForPattern[_last_event_index];
                    if ( c->position > totalTicks) {
                        break;
                    } else {
                        //Serial.printf("note: %d\t\t%d\t\t%.2f\r\n", c->position, c->isNoteStartEvent, c->rate);
                        onevent(c);
                        _last_event_index++;
                    }
                }

                if (wrapped) {
                    if (onloopend) onloopend(this, _currentPattern);
                    _last_event_index = 0;
                    if (_currentPattern != _nextPattern) {
                        _currentPattern = _nextPattern;
                        onloopchange(this, _nextPattern);
                    }
                }
            }
        }

        void start(unsigned long micros) {
            if (!_playing) {
                if (_numPatterns == 0)
                    addPattern(4);
                _previousMicroseconds = micros;
                _lastTickMicroseconds = _previousMicroseconds;
                _last_event_index = 0;
                _playing = true;
            }
        }

        std::function<void(sequencerevent *event)> onevent;
        std::function<void(sequencer *sequencer, int newPattern)> onloopchange;
        std::function<void(sequencer *sequencer, int pattern)> onloopend;

        void writenoteslist(unsigned pattern) {
            if (pattern >= _numPatterns) return;

            Serial.printf("list events in pattern: %d\r\n", pattern);
            vector<sequencerevent*> &sortedEventsForPatternPtr = _patterns[pattern]->_sorted_events;

            for (auto it = sortedEventsForPatternPtr.begin(); it != sortedEventsForPatternPtr.end(); it++)
            {
                sequencerevent *ev = *it;
                if (ev->isNoteStartEvent) {
                    Serial.printf("note: pos:%d\t\tnoteNo:%df\t\tch:%d\r\n", ev->position, ev->noteNumber, ev->channel);
                }
            }
        }

        pattern* addPattern(unsigned numBars) {
            pattern *result = new pattern();
            result->_loop_duration_bars = numBars;
            auto *sortedEventsForPattern = new vector<sequencerevent*>();
            _patterns.push_back(result);
            _numPatterns++;
            return result;
        }

        void setNextPattern(unsigned nextPattern) {
            if (nextPattern >= _numPatterns) return;
            _nextPattern = nextPattern;
        }

        void setNextPattern(pattern *nextPattern) {
            int index = getIndex<pattern*>(_patterns, nextPattern);
            if (index == -1){
                Serial.println("pattern does not belong to this sequencer...");
            } else 
                setNextPattern(index);
        }

    private:
        tempo &_tempo;
        songposition *_position;
        bool _playing = false;
        unsigned _numPatterns = 0;
        unsigned _currentPattern = 0;
        unsigned _nextPattern = 0;

        unsigned long _sixtyFourth = 0;
        unsigned long _lastTickMicroseconds = 0;
        unsigned long _microseconds = 0;
        unsigned long _previousMicroseconds = 0;
        vector<pattern *> _patterns;
        //vector<unsigned int> _loop_duration_bars;
        //vector< vector<sequencerevent*> * > _sorted_events; //store a collection of pointers to sequencerevents per pattern

        int _last_event_index = 0;

        template<class T>
        int getIndex(vector<T> v, T K)
        {
            auto it = find(v.begin(), v.end(), K);
            if (it != v.end())
            {
                return it - v.begin();
            }
            else {
                return -1;
            }
        }
    };

    class multisequencer {
    public:

        multisequencer(tempo &tempo) : _tempo(tempo) {
            _songposition = new songposition();
            _tempoSequencer = new sequencer(tempo, _songposition);
            _tempoSequencer->onevent = [&] (sequencerevent *event) {
                sequencertempoevent *evt = (sequencertempoevent*)event;
                Serial.printf("tempo: %.2f\n", evt->tempo);
                tempo.setBeatsPerMinute(evt->tempo);
            };
        }

        sequencer* newSequencer() {
            songposition *p = new songposition();
            sequencer *result = new sequencer(_tempo, p);
            result->onloopchange = [&] (sequencer *sequencer, int newPattern) {
                long index = indexOf(sequencer);
                onloopchange(index, newPattern);
            };
            _sequencers.push_back(result);
            _numSequencers++;
            return result;
        }

        sequencer* getSequencer(unsigned index) {
            return _sequencers[index];
        }

        sequencer* getTempoSequencer() {
            return _tempoSequencer;
        }

        long indexOf(sequencer *sequencer) {
            auto itr = std::find(_sequencers.begin(), _sequencers.end(), sequencer);
            if (itr != _sequencers.cend()) {
                return std::distance(_sequencers.begin(), itr);
            }
            else {
                return -1;
            }
        }

        void start(unsigned millis) {
            _tempoSequencer->start(millis);
            for (auto it = _sequencers.begin(); it != _sequencers.end(); it++) {
                sequencer *s = *it;
                s->start(millis);
            }
        }

        void tick(unsigned millis) {
            _tempoSequencer->tick(millis);
            for (auto it = _sequencers.begin(); it != _sequencers.end(); it++) {
                sequencer *s = *it;
                s->tick(millis);
            }
        }
        std::function<void(long channel, long pattern)> onloopchange;

    private:
        tempo &_tempo;
        unsigned _numSequencers = 0;
        vector<sequencer*> _sequencers;
        sequencer *_tempoSequencer;
        songposition *_songposition;

    };
}
#endif //TEENSYSEQUENCER_SEQUENCER_H
