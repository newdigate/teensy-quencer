//
// Created by Nicholas Newdigate on 16/07/2020.
//

#ifndef TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H
#define TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H

#include "Arduino.h"
#include "midireader.h"
#include "sequencer.h"
#include <cmath>

namespace newdigate {
    class midisequenceadapter {
    public:
        midisequenceadapter(multisequencer &multisequencer) :
            _multisequencer(multisequencer),
            _midifileReader() {
        }

        pattern* loadMidifileToChannelNumber(const char* filename, unsigned toSequencerChannel, unsigned midiFileTrackNumber, unsigned numBars, int transpose=0) {
            sequencer *seq = _multisequencer.getSequencer(toSequencerChannel);
            pattern* result = nullptr;
            if (seq)
                result = loadMidifileToNextPattern(filename, seq, midiFileTrackNumber, numBars, transpose);
            else
                Serial.printf("Sequencer channel %d not found...", toSequencerChannel);
            return result;
        }   

        void loadMidifile(const char* filename, pattern *pattern, unsigned midiFileTrackNumber, unsigned numBars, int transpose=0) {
            if (!_midifileReader.open(filename)) {
                Serial.printf("not able to open %s...\n", filename);
                return;
            }

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
                        event->channel = channelvoicemessage->getChannel();
                        event->position = totalTicks;
                        event->isNoteStartEvent = (channelvoicemessage->status & 0xF0) == 0x90 && channelvoicemessage->data2 > 0;
                        event->status = channelvoicemessage->status & 0xF0;
                        event->noteNumber = channelvoicemessage->data1 + transpose;
                        event->velocity = channelvoicemessage->data2;

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
                        pattern->addevent( event);

                        break; 
                    }
                    
                    case smftype_settempomessage : {
                        break;
                    }

                    default: 
                        break;
                }
            }        
            _midifileReader.close();
        }
        
        void loadMidiTempoTrack(const char* filename, pattern* pat, unsigned midiFileTrackNumber, unsigned numBars, int offsetBars) {
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
                        pat->addevent(event);
                        break;
                    }

                    default: 
                        break;
                }

                delete message;
            }
            sequencer->setNextPattern(pat);
        }

        pattern* loadMidifileToNextPattern(const char* filename, sequencer *seq, unsigned midiFileTrackNumber, unsigned numBars, int transpose=0) {
            pattern* pat = seq->addPattern(numBars);
            loadMidifile(filename, pat, midiFileTrackNumber, numBars, transpose);
            return pat;
        }

        pattern* loadMidiTempoTrackToNextPattern(const char* filename, unsigned midiFileTrackNumber, unsigned numBars, int offsetBars) {
            sequencer *sequencer = _multisequencer.getTempoSequencer();
            pattern* pat = sequencer->addPattern(numBars);
            loadMidiTempoTrack(filename, pat, midiFileTrackNumber, numBars,  offsetBars);
            return pat;
        }

        static double calcPitchFactor(uint8_t note, int transpose) {
            double result = pow(2.0, (note-36+transpose) / 12.0);
            return result;
        }

    private:
        midireader _midifileReader;
        multisequencer &_multisequencer;
    };
}

#endif //TEENSYSEQUENCER_MIDISEQUENCEADAPTER_H
