//
// Created by Nicholas Newdigate on 16/07/2020.
//

#ifndef TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H
#define TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H

#include "Arduino.h"
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

    void loadMidifileToNextChannelPattern(unsigned toSequencerChannel, unsigned midiFileTrackNumber, unsigned numBars, int transpose=0) {
        sequencer *sequencer = _multisequencer.getSequencer(toSequencerChannel);
        unsigned patternNumber = sequencer->addPattern(numBars);
        int polyphony = 0;
        _midifileReader.setTrackNumber(midiFileTrackNumber);
        midimessage message = {};
        long totalTicks = 0;
        while (_midifileReader.read(message)
               && totalTicks < numBars * 480 * 4) {
            totalTicks += message.delta_ticks;

            sequencerevent *event = new sequencerevent();
            event->channel = message.channel;
            //event->channel = 0;
            event->position = totalTicks;
            event->isNoteStartEvent = (message.status & 0xF0) == 0x90 && message.velocity > 0;
            event->status = message.status & 0xF0;
            event->noteNumber = message.key + transpose;
            event->velocity = message.velocity;

            if (event->isNoteStartEvent)
                polyphony++;
            else if (event->status == 0x80)
                polyphony--;

            //Serial.printf("Key: %d\t\tticks: %d\t\tPolyphony: %d\t\tstatus: %x\t\tisNoteOn:%d\t\tvelocity:%x\n", event->noteNumber, totalTicks, polyphony, message.status, event->isNoteStartEvent,event->velocity);

            sequencer->addevent(patternNumber, event);
        }
    }

    void loadMidiTempoTrack(unsigned midiFileTrackNumber, unsigned numBars, int offsetBars) {
        sequencer *sequencer = _multisequencer.getTempoSequencer();
        unsigned patternNumber = sequencer->addPattern(numBars);

        int polyphony = 0;
        _midifileReader.setTrackNumber(midiFileTrackNumber);
        midimessage message = {};
        long totalTicks = 0;
        while (_midifileReader.read(message)
               && totalTicks < numBars * 480 * 4) {
            totalTicks += message.delta_ticks;

            if (message.isTempoChange) {
                sequencertempoevent *event = new sequencertempoevent();

                event->tempo = message.tempo;
                event->position = totalTicks + (offsetBars * 480 * 4);
                Serial.printf("add tempo event: %x, %.2f\n", event->position, event->tempo );
                sequencer->addevent(patternNumber, event);
            }
        }
        sequencer->setNextPattern(patternNumber);
    }


    static double calcPitchFactor(uint8_t note, int transpose) {
        double result = pow(2.0, (note-36+transpose) / 12.0);
        return result;
    }

private:
    midireader _midifileReader;
    multisequencer &_multisequencer;
};


#endif //TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H
