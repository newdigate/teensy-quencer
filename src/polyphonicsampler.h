//
// Created by Nicholas Newdigate on 06/08/2020.
//

#ifndef TEENSYSEQUENCER_POLYPHONICSAMPLER_H
#define TEENSYSEQUENCER_POLYPHONICSAMPLER_H

#include "sequencer.h"

#define MAX_VOICES 16

typedef void (*noteEventCallback)(uint8_t noteNumber, uint8_t velocity, bool isNoteOn);

class polyphonicsampler {
public:
    polyphonicsampler() : noteOnFns() {
        for (int i=0; i < 128; i++)
          activeNotes[i] = 255;
        for (int i=0; i < 16; i++)
          activeVoices[i] = 255;
    }

    void noteOn(uint8_t noteNumber, uint8_t velocity) {
        int indexOfVoice = 255;
        if (activeNotes[noteNumber] == 255) {
            // note is not active, allocate a voice if possible
            indexOfVoice = getFirstFreeVoice();
            if (indexOfVoice < numVoices) {
                activeVoices[indexOfVoice] = noteNumber;
                activeNotes[noteNumber] = indexOfVoice;
            } else
            {
                // note dropped: insufficient polyphony to play this note
                indexOfVoice = 255;
            }
        } else {
            // note is already active, just re-trigger it...
            indexOfVoice = activeNotes[noteNumber];
        }
        if (indexOfVoice != 255) {
            noteEventCallback noteOnFunction = noteOnFns[indexOfVoice];
            noteOnFunction(noteNumber, velocity, true);
        }
    }

    void noteOff(uint8_t noteNumber) {
        uint8_t index = activeNotes[noteNumber];
        if (index == 255) {
            // note is not active, ignore
            return;
        }

        noteEventCallback noteOnFunction = noteOnFns[index];
        noteOnFunction(noteNumber, 0, false);
        activeNotes[noteNumber] = 255;
        activeVoices[index] = 255; // free the voice
    }

    void pushNoteFunction (const noteEventCallback &noteOnFunction) {
        noteOnFns[numVoices] =  noteOnFunction;
        numVoices++;
    }

private:
    noteEventCallback noteOnFns[MAX_VOICES];
    uint8_t activeNotes[128];
    uint8_t activeVoices[MAX_VOICES];
    uint8_t numVoices = 0;

    uint8_t getFirstFreeVoice() {
        for (int i=0; i < numVoices; i++) {
            if (activeVoices[i] == 255) {
                return i;
            }
        }
        return 255;
    }
};


#endif //TEENSYSEQUENCER_POLYPHONICSAMPLER_H
