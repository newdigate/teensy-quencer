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
    sequencer(tempo &tempo, songposition &position) : _tempo(tempo), _position(position) {}

    void tick(unsigned long millisecs) {
        if (!_playing) return;
        _milliseconds = millisecs;

        unsigned long deltaMillis = _milliseconds - _lastSixtyFourthMillis;
        if (deltaMillis >= _tempo._milliseconds_per_64th) {
            _lastSixtyFourthMillis = millisecs;

            unsigned long deltaSixtyFourths = deltaMillis / _tempo._milliseconds_per_64th;
            _position.sixtyFourth += deltaSixtyFourths;
            _position.totalSixtyFourth += deltaSixtyFourths;
            if (_position.sixtyFourth >= 64) {
                _position.beat += _position.sixtyFourth / 64;
                _position.sixtyFourth %= 64;
            }
            if (_position.beat > 4) {
                _position.bar += _position.beat / 4;
                _position.beat %= 4;
            }

            unsigned long totalSixtyFourth = _position.totalSixtyFourth;
            bool wrapped = false;
            if (_position.bar > _loop_duration_bars) {
                _position.bar %= _loop_duration_bars;
                _position.sixtyFourth %= 64 * 4 *  _loop_duration_bars;
                _position.totalSixtyFourth %= 64 * 4 * _loop_duration_bars;
                wrapped = true;
            }

            while (_last_event_index < events.size() ) {
                sequencerevent* c = _sorted_events[_last_event_index];
                if ( c->position > totalSixtyFourth) {
                    break;
                } else {
                    onevent(c);
                    _last_event_index++;
                }
            }

            if (wrapped)
                _last_event_index = 0;

        }
    }

    void start(unsigned long millis) {
        if (!_playing) {
            _previousMilliseconds = millis;
            _lastSixtyFourthMillis = _previousMilliseconds;
            _last_event_index = 0;
            _playing = true;
        }
    }

    std::function<void(sequencerevent *event)> onevent;

    void addelement(loopelement *element) {
        elements.push_back(element);
        sequencerevent *start = new sequencerevent();
        start->channel = element->channel;
        start->position = element->start_tick;
        start->isNoteStartEvent = true;
        start->rate = element->rate;
        start->parent = element;
        events.insert(start);

        sequencerevent *end = new sequencerevent();
        end->channel = element->channel;
        end->position = element->stop_tick;
        end->isNoteStartEvent = false;
        end->rate = 0.0f;
        end->parent = element;
        events.insert(end);

        _sorted_events.clear();
        for(std::set<sequencerevent*>::iterator i = events.begin(); i != events.end(); ++i) {
            sequencerevent *event = *i;
            _sorted_events.push_back(event);
        }
    }

private:
    tempo &_tempo;
    songposition &_position;
    bool _playing = false;

    unsigned long _sixtyFourth = 0;
    unsigned long _lastSixtyFourthMillis = 0;
    unsigned long _milliseconds = 0;
    unsigned long _previousMilliseconds = 0;
    int _loop_duration_bars = 4;
    std::vector<loopelement*> elements;
    std::vector<sequencerevent*> _sorted_events;
    
    std::set<sequencerevent*, sequencerevent> events;
    int _last_event_index = 0;
};


#endif //TEENSYSEQUENCER_SEQUENCER_H
