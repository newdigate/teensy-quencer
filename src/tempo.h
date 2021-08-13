//
// Created by Nicholas Newdigate on 29/06/2020.
//

#ifndef TEENSYSEQUENCER_TEMPO_H
#define TEENSYSEQUENCER_TEMPO_H

namespace newdigate {
struct tempo {
    unsigned long _microseconds_per_tick = 0;
    double _beats_per_minute = 140.0;

    tempo(double beats_per_minute) {
        _beats_per_minute = beats_per_minute;
        _microseconds_per_tick = get_microseconds_per_tick();
    }

    tempo() {
        _microseconds_per_tick = get_microseconds_per_tick();
    }

    void setBeatsPerMinute(double beats_per_minute) {
        _beats_per_minute = beats_per_minute;
        _microseconds_per_tick = get_microseconds_per_tick();
    }

    unsigned int get_microseconds_per_tick() {
        double micros_per_beat = 60000000.0 / _beats_per_minute;
        unsigned int micros_per_tick = micros_per_beat / 480;
        return micros_per_tick;
    }
};
}

#endif //TEENSYSEQUENCER_TEMPO_H
