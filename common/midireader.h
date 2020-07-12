//
// Created by Nicholas Newdigate on 10/04/2018.
//
#ifndef TEENSYQUENCER_COMMON_MIDIREADER_H
#define TEENSYQUENCER_COMMON_MIDIREADER_H

#include <vector>
#include <functional>
#include <algorithm>

#if ARDUINO >= 100
#include "Arduino.h"
#include <SD.h>
#else
#include "../teensy_cores_x86/mock_arduino.h"
#include "../teensy_cores_x86/SD/SD.h"
#endif

#include <string>

using namespace std;

struct midimessage {
    uint32_t delta_ticks;
    unsigned char status;
    unsigned char key;
    unsigned char velocity;
    unsigned char channel;
};

class midireader {
public:
    midireader() :
            _filename(),
            _midifile(),
            _initialized(false),
            _track_offset(),
            _track_size()
    {

    };

    bool open(const char* filename);
    bool setTrackNumber(unsigned char trackNumber);
    bool read(midimessage &midiMessage);

    unsigned getNumTracks() {
        return _numTracks;
    }

private:
    bool _initialized;
    File _midifile;
    char* _filename;
    unsigned _pulses_per_quater_note;
    float _current_beats_per_minute = 120.0;
    int _current_track = -1;
    unsigned _currentTrackOffset = 0;
    unsigned _numTracks = 0;
    vector<unsigned long> _track_size;
    vector<unsigned long> _track_offset;

    void readMetaText();

    const char * voice_message_status_name(unsigned char status);
};


#endif //TEENSYQUENCER_COMMON_MIDIREADER_H
