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

    int loadMidifileToChannelNumber(unsigned toSequencerChannel, unsigned midiFileTrackNumber, unsigned numBars, int transpose=0) {
        sequencer *seq = _multisequencer.getSequencer(toSequencerChannel);
        if (seq)
            return loadMidifileToNextPattern(seq, numBars, transpose);
        else
            Serial.printf("Sequencer channel %d not found...", toSequencerChannel);
        
        return -1;
    }   

    void loadMidifile(sequencer *seq, unsigned patternNumber, unsigned midiFileTrackNumber, unsigned numBars, int transpose=0) {
        int polyphony = 0;
        _midifileReader.setTrackNumber(midiFileTrackNumber);
        long totalTicks = 0;
        smfmidimessage *message;
        while (((message = _midifileReader.read()) != nullptr)
               && totalTicks < numBars * 480 * 4) {
            totalTicks += message->delta_ticks;

            switch(message->getMessageType()) {
                case smftype_channelvoicemessage : {
                    smfchannelvoicemessage *channelvoicemessage = (smfchannelvoicemessage *)message;

                    sequencerevent *event = new sequencerevent();
                    event->channel = channelvoicemessage->channel;
                    //event->channel = 0;
                    event->position = totalTicks;
                    event->isNoteStartEvent = (channelvoicemessage->data1 & 0xF0) == 0x90 && channelvoicemessage->data3 > 0;
                    event->status = channelvoicemessage->data1 & 0xF0;
                    event->noteNumber = channelvoicemessage->data2 + transpose;
                    event->velocity = channelvoicemessage->data3;

                    if (event->isNoteStartEvent)
                        polyphony++;
                    else if (event->status == 0x80)
                        polyphony--;

                    /*
                    Serial.printf("Key: %d\t\tticks: %d\t\tPolyphony: %d\t\tstatus: %x\t\tisNoteOn:%d\t\tvelocity:%x\n", 
                        event->noteNumber, 
                        totalTicks, 
                        polyphony, 
                        event->status, 
                        event->isNoteStartEvent,
                        event->velocity);
                        */
                    seq->addevent(patternNumber, event);

                    break; 
                }
                
                case smftype_settempomessage : {
                    break;
                }

                default: 
                    break;
            }
        }        
    }
    
    void loadMidiTempoTrack(unsigned patternNumber, unsigned midiFileTrackNumber, unsigned numBars, int offsetBars) {
        sequencer *sequencer = _multisequencer.getTempoSequencer();

        int polyphony = 0;
        long totalTicks = 0;
        _midifileReader.setTrackNumber(midiFileTrackNumber);

        smfmidimessage *message;
        while (((message = _midifileReader.read()) != nullptr)
               && totalTicks < numBars * 480 * 4) {
            totalTicks += message->delta_ticks;

            switch(message->getMessageType()) {

                case smftype_settempomessage : {
                    smfsettempomessage *tempomessage = (smfsettempomessage *)message;
                    sequencertempoevent *event = new sequencertempoevent();
                    event->tempo = tempomessage->getTempo();
                    event->position = totalTicks + (offsetBars * 480 * 4);
                    //Serial.printf("add tempo event: %x, %.2f\n", event->position, event->tempo );
                    sequencer->addevent(patternNumber, event);
                    break;
                }

                default: 
                    break;
            }

            delete message;
        }
        sequencer->setNextPattern(patternNumber);
    }

    int loadMidifileToNextPattern(sequencer *seq, unsigned midiFileTrackNumber, unsigned numBars, int transpose=0) {
        unsigned patternNumber = seq->addPattern(numBars);
        loadMidifile(seq, patternNumber, midiFileTrackNumber, numBars, transpose);
        return patternNumber;
    }

    int loadMidiTempoTrackToNextPattern(unsigned midiFileTrackNumber, unsigned numBars, int offsetBars) {
        sequencer *sequencer = _multisequencer.getTempoSequencer();
        unsigned patternNumber = sequencer->addPattern(numBars);
        loadMidiTempoTrack(patternNumber, midiFileTrackNumber, numBars,  offsetBars);
        return patternNumber;
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
