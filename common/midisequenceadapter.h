//
// Created by Nicholas Newdigate on 16/07/2020.
//

#ifndef TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H
#define TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H

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

    void loadMidifileToNextChannelPattern(unsigned toSequencerChannel, unsigned midiFileTrackNumber, unsigned numBars){
        sequencer* sequencer = _multisequencer.getSequencer(toSequencerChannel);
        unsigned patternNumber = sequencer->addPattern(numBars);

        _midifileReader.setTrackNumber(midiFileTrackNumber);
        midimessage message = {};
        long totalTicks = 0;
        while (_midifileReader.read(message)
               && totalTicks < numBars * 256 * 4 ){
            totalTicks += message.delta_ticks;
            sequencerevent *event = new sequencerevent();
            event->channel = message.channel;
            event->position = totalTicks;
            event->isNoteStartEvent = message.status == 0x90 && message.velocity > 0;
            event->rate = calcPitchFactor(message.key);
            sequencer->addevent(patternNumber, event );
        }
        sequencer->closeAllPendingEvents(patternNumber);
    }

    static double calcPitchFactor(uint8_t note) {
        double result = pow(2.0, (note-60) / 12.0);
        return result;
    }

private:
    midireader _midifileReader;
    multisequencer &_multisequencer;
};


#endif //TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H
