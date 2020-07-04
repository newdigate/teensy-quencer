//
// Created by Nicholas Newdigate on 29/06/2020.
//

#ifndef TEENSYSEQUENCER_SEQUENCER_H
#define TEENSYSEQUENCER_SEQUENCER_H

#include <set>
#include <vector>
#include <functional>

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
    float rate = 1.0f;
};

struct sequencerevent {
    uint8_t channel = 0;
    long position = 0;
    bool isNoteStartEvent = true;
    float rate = 1.0;
    loopelement *parent = NULL;

    bool operator ()(sequencerevent *lhs, const sequencerevent *rhs) const
    {
        return lhs->position < rhs->position;
    }
};

class sequencer {
public:
    sequencer(tempo &tempo, songposition *position) : _tempo(tempo), _position(position) {}

    void tick(unsigned long millisecs) {
        if (!_playing) return;
        _milliseconds = millisecs;

        unsigned long deltaMillis = _milliseconds - _lastSixtyFourthMillis;
        if (deltaMillis >= _tempo._milliseconds_per_64th) {
            _lastSixtyFourthMillis = millisecs;

            unsigned long deltaSixtyFourths = deltaMillis / _tempo._milliseconds_per_64th;
            _position->sixtyFourth += deltaSixtyFourths;
            _position->totalSixtyFourth += deltaSixtyFourths;
            if (_position->sixtyFourth >= 64) {
                _position->beat += _position->sixtyFourth / 64;
                _position->sixtyFourth %= 64;
            }
            if (_position->beat > 4) {
                _position->bar += _position->beat / 4;
                _position->beat %= 4;
            }

            unsigned long totalSixtyFourth = _position->totalSixtyFourth;
            bool wrapped = false;
            if (_position->bar > _loop_duration_bars) {
                _position->bar %= _loop_duration_bars;
                _position->sixtyFourth %= 64 * 4 *  _loop_duration_bars;
                _position->totalSixtyFourth %= 64 * 4 * _loop_duration_bars;
                wrapped = true;
            }
        
            vector<sequencerevent*> *sortedEventsForPattern = _sorted_events[_currentPattern];
            while (_last_event_index < sortedEventsForPattern->size() ) {
                sequencerevent* c = (*sortedEventsForPattern)[_last_event_index];
                if ( c->position > totalSixtyFourth) {
                    break;
                } else {
                    onevent(c);
                    _last_event_index++;
                }
            }

            if (wrapped) {
                _last_event_index = 0;
                _currentPattern = _nextPattern;
            }
        }
    }

    void start(unsigned long millis) {
        if (!_playing) {
            if (_numPatterns == 0)
                addPattern();
            _previousMilliseconds = millis;
            _lastSixtyFourthMillis = _previousMilliseconds;
            _last_event_index = 0;
            _playing = true;
        }
    }

    std::function<void(sequencerevent *event)> onevent;

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
                pixel[ev->channel][ev->position/16] = 'X';
                unsigned length = (ev->parent->stop_tick - ev->parent->start_tick)/16;
                for (int k=0; k < length; k++) {
                    int x = (ev->position/16) + k + 1;
                    if (x < 80)
                        pixel[ev->channel][x] = '-';
                }
            }
        }

        Serial.println();
        for (int j=0; j < 8; j++) {
            for (int i=0; i < 80; i++) {
                if (i % 16 == 0)
                    Serial.print("|");
                if (i % 4 == 0)
                    Serial.print(" ");
                Serial.print(pixel[j][i]);
            }
            Serial.println();
        }
    }



    void addPattern() {
        vector<loopelement*> *elementsForPattern = new vector<loopelement*>();
        _elements.push_back(elementsForPattern);

        vector<sequencerevent*> *sortedEventsForPattern = new vector<sequencerevent*>();
        _sorted_events.push_back(sortedEventsForPattern);

        _numPatterns++;
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
        end->rate = 0.0f;
        end->parent = element;
        eventsForPattern.insert(end);

        sortedEventsForPatternPtr->clear();
        for(auto &&event:eventsForPattern) {
            sortedEventsForPatternPtr->push_back(event);
        }
    }

private:
    tempo &_tempo;
    songposition *_position;
    bool _playing = false;
    unsigned _numPatterns = 0;
    unsigned _currentPattern = 0;
    unsigned _nextPattern = 0;

    unsigned long _sixtyFourth = 0;
    unsigned long _lastSixtyFourthMillis = 0;
    unsigned long _milliseconds = 0;
    unsigned long _previousMilliseconds = 0;
    int _loop_duration_bars = 4;
    vector< vector<loopelement*> * > _elements;
    vector< vector<sequencerevent*> * > _sorted_events;
    

    int _last_event_index = 0;
};

class multisequencer {
public:

    multisequencer(tempo &tempo) : _tempo(tempo) {

    }

    sequencer* newSequencer() {
        songposition *p = new songposition();
        sequencer *result = new sequencer(_tempo, p);
        _sequencers.push_back(result);
        _numSequencers++;
        return result;
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

private:
    tempo &_tempo;
    unsigned _numSequencers = 0;
    vector<sequencer*> _sequencers;
};
#endif //TEENSYSEQUENCER_SEQUENCER_H
