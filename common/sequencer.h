//
// Created by Nicholas Newdigate on 29/06/2020.
//

#ifndef TEENSYSEQUENCER_SEQUENCER_H
#define TEENSYSEQUENCER_SEQUENCER_H

#include "tempo.h"
#include "songposition.h"

class sequencer {
public:
    sequencer(tempo &tempo) : _tempo(tempo) {}

    void tick(unsigned long millisecs) {
        _previousMilliseconds = _milliseconds;
        _milliseconds = millisecs;

        unsigned long deltaMillis = _milliseconds - _lastSixtyFourthMillis;
        if (deltaMillis >= _milliseconds_per_64th) {
            _lastSixtyFourthMillis = millisecs;

            unsigned long deltaSixtyFourths = deltaMillis / _milliseconds_per_64th;
            _position.sixtyFourth += deltaSixtyFourths;
            if (_position.sixtyFourth >= 64) {
                _position.beat += deltaSixtyFourths / 64;
                _position.sixtyFourth %= 64;
            }
            if (_position.beat >= 4) {
                _position.bar += _position.beat / 4;
                _position.beat %= 4;
            }
        }
    }

private:
    tempo &_tempo;
    songposition _position;
    unsigned long _milliseconds_per_64th = 0;
    unsigned long _sixtyFourth = 0;
    unsigned long _lastSixtyFourthMillis = 0;
    unsigned long _milliseconds = 0;
    unsigned long _previousMilliseconds = 0;
    int _loop_duration_bars = 16;
};


#endif //TEENSYSEQUENCER_SEQUENCER_H
