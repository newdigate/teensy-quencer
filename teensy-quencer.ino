#include <Audio.h>
#include <SPI.h>
#include <SD.h>

#include "common/sequencer.h"
#include "common/songposition.h"
#include "common/tempo.h"
#include "common/looptype.h"

tempo tempo(120.0f);
songposition position;
sequencer sequencer(tempo, position);

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdRaw1;     //xy=178,383
AudioPlaySdWav           playSdRaw2;     //xy=205,172
AudioPlaySdWav           playSdRaw3;     //xy=223,285
AudioMixer4              mixer1;         //xy=466,197
AudioMixer4              mixer2;         //xy=480,316
AudioOutputTDM           tdm3;           //xy=740,249
AudioConnection          patchCord1(playSdRaw3, 0, mixer1, 2);
AudioConnection          patchCord2(playSdRaw3, 1, mixer2, 2);
AudioConnection          patchCord3(playSdRaw1, 0, mixer1, 0);
AudioConnection          patchCord4(playSdRaw1, 1, mixer2, 0);
AudioConnection          patchCord5(playSdRaw2, 0, mixer1, 1);
AudioConnection          patchCord6(playSdRaw2, 1, mixer2, 1);
AudioConnection          patchCord7(mixer1, 0, tdm3, 0);
AudioConnection          patchCord8(mixer1, 0, tdm3, 4);
AudioConnection          patchCord9(mixer1, 0, tdm3, 8);
AudioConnection          patchCord10(mixer1, 0, tdm3, 12);
AudioConnection          patchCord11(mixer2, 0, tdm3, 2);
AudioConnection          patchCord12(mixer2, 0, tdm3, 6);
AudioConnection          patchCord13(mixer2, 0, tdm3, 10);
AudioConnection          patchCord14(mixer2, 0, tdm3, 14);
AudioControlCS42448      cs42448_1;      //xy=739,495
// GUItool: end automatically generated code


const char* _filename1 = "KICK007.RAW"; 

void setup() {
  AudioMemory(60);
  Serial.begin(9600);    
  
  //while (!Serial) { yield(); }

  
  if (!(SD.begin(BUILTIN_SDCARD))) {
      // stop here if no SD card, but print a message
      while (1) {
          Serial.println("Unable to access the SD card");
          delay(500);
      }
  }

  delay(5);
  
  AudioNoInterrupts();  // disable audio library momentarily
  // put your setup code here, to run once:
  //cs42448_1.setAddress(0);
  cs42448_1.enable();
  cs42448_1.volume(1);
  //cs42448_1.inputLevel(1);
  AudioInterrupts();   

  sequencer.onevent = [] (sequencerevent *event) {
      Serial.printf("%d:%d:%4f\n", position.bar, position.beat, position.sixtyFourth / 64.0f);
      Serial.printf("----- %d:%d:%4f\n", event->channel, event->isNoteStartEvent, event->rate);

      switch(event->channel) {
        case 1: 
          if (event->isNoteStartEvent) {
  
            if (playSdRaw2.isPlaying())
              playSdRaw2.stop();

            playSdRaw2.play("BASS.WAV");
          } else {
            if (playSdRaw2.isPlaying())
              playSdRaw2.stop();            
          }
          break;


        
        case 2: 
          if (event->isNoteStartEvent) {
  
            if (playSdRaw1.isPlaying())
              playSdRaw1.stop();

            playSdRaw1.play("KICK.WAV");
          } else {
            if (playSdRaw1.isPlaying())
              playSdRaw1.stop();            
          }
          break;

        case 3: 
          if (event->isNoteStartEvent) {
  
            if (playSdRaw3.isPlaying())
              playSdRaw3.stop();

            playSdRaw3.play("SNARE.WAV");
          } else {
            if (playSdRaw3.isPlaying())
              playSdRaw3.stop();            
          }
          break;
          
          
        default:
          break;
      }
  };

  for (int i=0; i < 16; i++) {
      loopelement *kick = new loopelement();
      kick->rate = 1.0f;
      kick->start_tick = (i * 16 * 4);
      kick->stop_tick = (i * 16 * 4) + 15;
      kick->channel = 2;
      kick->loopType = looptypex_none;
      sequencer.addelement(kick);
  }

  for (int i=0; i < 16; i++) {
      loopelement *kick = new loopelement();
      kick->rate = 1.0f;
      kick->start_tick = ((i+2) * 16 * 4);
      kick->stop_tick = ((i+2) * 16 * 4) + 15;
      kick->channel = 3;
      kick->loopType = looptypex_none;
      sequencer.addelement(kick);
  }

  for (int i=0; i < 32; i++) {
      loopelement *snare = new loopelement();
      snare->rate = 1.0f;
      snare->start_tick = ((i+2) * 8 * 4);
      snare->stop_tick = ((i+2) * 8 * 4) + 15;
      snare->channel = 1;
      snare->loopType = looptypex_none;
      sequencer.addelement(snare);
  }
 
  sequencer.start(millis());

  mixer1.gain(0, 1);
  mixer1.gain(1, 1);
  mixer1.gain(2, 1);
  mixer1.gain(3, 1);

  mixer2.gain(0, 1);
  mixer2.gain(1, 1);
  mixer2.gain(2, 1);
  mixer2.gain(3, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  sequencer.tick(millis());
}

unsigned __exidx_start;
unsigned __exidx_end;
