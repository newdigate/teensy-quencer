//
// Created by Nicholas Newdigate on 29/06/2020.
//

#ifndef TEENSYSEQUENCER_SEQUENCER_H
#define TEENSYSEQUENCER_SEQUENCER_H

#include "tempo.h"
#include "songposition.h"
#include "../teensy_cores_x86/mock_arduino.h"

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
            if (_position.sixtyFourth >= 64) {
                _position.beat += _position.sixtyFourth / 64;
                _position.sixtyFourth %= 64;
            }
            if (_position.beat >= 4) {
                _position.bar += _position.beat / 4;
                _position.beat %= 4;
            }
        }
    }

    void start() {
        if (!_playing) {
            _previousMilliseconds = millis();
            _lastSixtyFourthMillis = _previousMilliseconds;
            _playing = true;
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
    int _loop_duration_bars = 16;
};


#endif //TEENSYSEQUENCER_SEQUENCER_H
