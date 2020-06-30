//
// Created by Nicholas Newdigate on 29/06/2020.
//

#ifndef TEENSYSEQUENCER_TEMPO_H
#define TEENSYSEQUENCER_TEMPO_H


struct tempo {
    unsigned long _milliseconds_per_64th = 0;
    float _beats_per_minute = 120.0f;

    tempo(float beats_per_minute) {
        _beats_per_minute = beats_per_minute;
        _milliseconds_per_64th = get_milliseconds_per_tick();
    }

    tempo() {
        _milliseconds_per_64th = get_milliseconds_per_tick();
    }

    void setBeatsPerMinute(float beats_per_minute) {
        _beats_per_minute = beats_per_minute;
        _milliseconds_per_64th = get_milliseconds_per_tick();
    }

    unsigned int get_milliseconds_per_tick() {
        float seconds_per_beat = 60.0f / _beats_per_minute;
        unsigned int millis_per_beat = seconds_per_beat * 1000.0f;
        unsigned int millis_per_tick = millis_per_beat / 64;
        return millis_per_tick;
    }
};


#endif //TEENSYSEQUENCER_TEMPO_H
