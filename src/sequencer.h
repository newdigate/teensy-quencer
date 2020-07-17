//
// Created by Nicholas Newdigate on 29/06/2020.
//

#ifndef TEENSYSEQUENCER_SEQUENCER_H
#define TEENSYSEQUENCER_SEQUENCER_H

#include <set>
#include <vector>
#include <functional>
#include <algorithm>

#include "tempo.h"
#include "songposition.h"
#include "looptype.h"

#ifdef ARDUINO
#include <Arduino.h>
#else
#include "../teensy_cores_x86/mock_arduino.h"
#endif

using namespace std;

struct loopelement {
    uint8_t channel = 0;
    long start_tick = 0;
    long stop_tick = 0;
    looptype_x loopType = looptypex_none;
    double rate = 1.0;
};

struct sequencerevent {
    uint8_t channel = 0;
    long position = 0;
    bool isNoteStartEvent = true;
    double rate = 1.0;
    loopelement *parent = NULL;

    bool operator ()(sequencerevent *lhs, const sequencerevent *rhs) const
    {
        return lhs->position < rhs->position;
    }
};

class sequencer {
public:
    sequencer(tempo &tempo, songposition *position) : _tempo(tempo), _position(position) {}

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
            if (_position->bar > _loop_duration_bars[_currentPattern]) {
                _position->bar %= _loop_duration_bars[_currentPattern];
                _position->ticks %= 480 * 4 *  _loop_duration_bars[_currentPattern];
                _position->totalTicks %= 480 * 4 * _loop_duration_bars[_currentPattern];
                wrapped = true;
            }
        
            vector<sequencerevent*> *sortedEventsForPattern = _sorted_events[_currentPattern];
            while (_last_event_index < sortedEventsForPattern->size() ) {
                sequencerevent* c = (*sortedEventsForPattern)[_last_event_index];
                if ( c->position > totalTicks) {
                    break;
                } else {
                    Serial.printf("note: %d\t\t%d\t\t%.2f\r\n", c->position, c->isNoteStartEvent, c->rate);
                    onevent(c);
                    _last_event_index++;
                }
            }

            if (wrapped) {
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

    void writescore(unsigned pattern) {
        if (pattern >= _numPatterns) return;

        Serial.printf("pattern: %d", pattern);
        vector<sequencerevent*> *sortedEventsForPatternPtr = _sorted_events[pattern];

        char pixel[8][80];
        memset(pixel, '.',  80*8);
        for (auto it = sortedEventsForPatternPtr->begin(); it != sortedEventsForPatternPtr->end(); it++)
        {
            sequencerevent *ev = *it;
            if (ev->isNoteStartEvent) {
                pixel[ev->channel][ev->position/(120)] = 'X';
                unsigned length = (ev->parent->stop_tick - ev->parent->start_tick)/120;
                for (int k=0; k < length; k++) {
                    int x = (ev->position/120) + k + 1;
                    if (x < 80)
                        pixel[ev->channel][x] = '-';
                }
            }
        }

        Serial.println();
        for (int j=0; j < 8; j++) {
            for (int i=0; i < 80; i++) {
                if (i % 16 == 0)
                    Serial.print('|');
                if (i % 4 == 0)
                    Serial.print(' ');
                Serial.print(pixel[j][i]);
            }
            Serial.println();
        }
    }

    void writenoteslist(unsigned pattern) {
        if (pattern >= _numPatterns) return;

        Serial.printf("list events in pattern: %d\r\n", pattern);
        vector<sequencerevent*> *sortedEventsForPatternPtr = _sorted_events[pattern];

        for (auto it = sortedEventsForPatternPtr->begin(); it != sortedEventsForPatternPtr->end(); it++)
        {
            sequencerevent *ev = *it;
            if (ev->isNoteStartEvent) {
                unsigned length = (ev->parent->stop_tick - ev->parent->start_tick);
                Serial.printf("note: pos:%d\t\tlen:%d\t\trate:%.2f\t\tch:%d\r\n", ev->position, length, ev->rate, ev->channel);
            }
        }
    }


    unsigned int addPattern(unsigned numBars) {
        auto *elementsForPattern = new vector<loopelement*>();
        _elements.push_back(elementsForPattern);

        auto *sortedEventsForPattern = new vector<sequencerevent*>();
        _sorted_events.push_back(sortedEventsForPattern);

        auto *pendingEventsForPattern = new vector<sequencerevent*>();
        _pending_events.push_back(pendingEventsForPattern);

        _loop_duration_bars.push_back(numBars);

        unsigned int result = _numPatterns;
        _numPatterns++;
        return result;
    }

    void setNextPattern(unsigned nextPattern) {
        if (nextPattern >= _numPatterns) return;
        _nextPattern = nextPattern;
    }

    void addelement(unsigned pattern, loopelement *element) {
        if (pattern >= _numPatterns) return;

        vector<loopelement*> *elementsForPattern = _elements[pattern];
        elementsForPattern->push_back(element);

        vector<sequencerevent*> *sortedEventsForPatternPtr = _sorted_events[pattern];

        multiset<sequencerevent*, sequencerevent> eventsForPattern;
        eventsForPattern.insert(sortedEventsForPatternPtr->begin(), sortedEventsForPatternPtr->end());

        sequencerevent *start = new sequencerevent();
        start->channel = element->channel;
        start->position = element->start_tick;
        start->isNoteStartEvent = true;
        start->rate = element->rate;
        start->parent = element;
        eventsForPattern.insert(start);

        sequencerevent *end = new sequencerevent();
        end->channel = element->channel;
        end->position = element->stop_tick;
        end->isNoteStartEvent = false;
        end->rate = 1.0f;
        end->parent = element;
        eventsForPattern.insert(end);

        sortedEventsForPatternPtr->clear();
        for(auto &&event:eventsForPattern) {
            sortedEventsForPatternPtr->push_back(event);
        }
    }

    void addevent(unsigned pattern, sequencerevent *event) {
        if (pattern >= _numPatterns) return;
        vector<sequencerevent*> *pendingEventsForPatternPtr = _pending_events[pattern];

        if (event->isNoteStartEvent) {
            pendingEventsForPatternPtr->push_back( event );
        } else{

            // first corresponding note-on event
            sequencerevent *correspondingNoteOnEvent = nullptr;
            for (const auto & eventToCheck : *pendingEventsForPatternPtr){
                if (eventToCheck->rate == event->rate) {
                    correspondingNoteOnEvent = eventToCheck;
                    auto it = std::find(pendingEventsForPatternPtr->begin(), pendingEventsForPatternPtr->end(), correspondingNoteOnEvent);
                    if(it != pendingEventsForPatternPtr->end())
                        pendingEventsForPatternPtr->erase(it);
                    break;
                }
            }
            if (correspondingNoteOnEvent != nullptr) {
                auto *loopelement = new struct loopelement();
                loopelement->start_tick = correspondingNoteOnEvent->position;
                loopelement->stop_tick = event->position;
                loopelement->rate = correspondingNoteOnEvent->rate;
                addelement(pattern, loopelement);
            }
        }
    }

    void closeAllPendingEvents(unsigned pattern) {
        if (pattern >= _numPatterns) return;
        vector<sequencerevent*> *pendingEventsForPatternPtr = _pending_events[pattern];
        unsigned numBarsForPattern = _loop_duration_bars[pattern];
        for (const auto & pendingevent : *pendingEventsForPatternPtr) {
            auto *loopelement = new struct loopelement();
            loopelement->start_tick = pendingevent->position;
            loopelement->stop_tick = numBarsForPattern * 4 * 256;
            loopelement->rate = pendingevent->rate;
            addelement(pattern, loopelement);
        }
        pendingEventsForPatternPtr->clear();
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
    vector<unsigned int> _loop_duration_bars;
    vector< vector<loopelement*> * > _elements;
    vector< vector<sequencerevent*> * > _sorted_events;

    vector< vector<sequencerevent*> * > _pending_events;

    int _last_event_index = 0;
};

class multisequencer {
public:

    multisequencer(tempo &tempo) : _tempo(tempo) {

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
        for (auto it = _sequencers.begin(); it != _sequencers.end(); it++) {
            sequencer *s = *it;
            s->start(millis);
        }
    }

    void tick(unsigned millis) {
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

};
#endif //TEENSYSEQUENCER_SEQUENCER_H
