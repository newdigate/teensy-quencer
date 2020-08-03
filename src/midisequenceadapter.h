//
// Created by Nicholas Newdigate on 16/07/2020.
//

#ifndef TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H
#define TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#endif

#include "midireader.h"
#include "sequencer.h"
#include <cmath>

class midisequenceadapter {
public:
    midisequenceadapter(multisequencer &multisequencer) :
        _multisequencer(multisequencer),
        _midifileReader() {
    }
    bool loadMidi(const char* filename){
        return _midifileReader.open(filename);
    }
    void close() {
        _midifileReader.close();
    }

    void loadMidifileToNextChannelPattern(unsigned toSequencerChannel, unsigned midiFileTrackNumber, unsigned numBars, int transpose=0){
        sequencer* sequencer = _multisequencer.getSequencer(toSequencerChannel);
        unsigned patternNumber = sequencer->addPattern(numBars);

        _midifileReader.setTrackNumber(midiFileTrackNumber);
        midimessage message = {};
        long totalTicks = 0;
        while (_midifileReader.read(message)
               && totalTicks < numBars * 480 * 4){
            totalTicks += message.delta_ticks;

            sequencerevent *event = new sequencerevent();
            //event->channel = message.channel;
            event->channel = 0;
            event->position = totalTicks;
            event->isNoteStartEvent = (message.status & 0xF0) == 0x90 && message.velocity > 0;
            event->rate = calcPitchFactor(message.key, transpose);

            //Serial.printf("total ticks: %d - (ch:%d, pos:%d, noteOn:%x, rate:%.2f)\r\n", totalTicks, event->channel, event->position, event->isNoteStartEvent, event->rate);

            sequencer->addevent(patternNumber, event );
        }
        sequencer->closeAllPendingEvents(patternNumber);
    }

    static double calcPitchFactor(uint8_t note, int transpose) {
        double result = pow(2.0, (note-60+transpose) / 12.0);
        return result;
    }

private:
    midireader _midifileReader;
    multisequencer &_multisequencer;
};


#endif //TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H
