#include <Audio.h>
#include <SPI.h>
#include <SD.h>

#include "common/sequencer.h"
#include "common/songposition.h"
#include "common/tempo.h"
#include "common/looptype.h"

tempo tempo(120.0f);

multisequencer multisequencer(tempo);

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdRaw6;     //xy=180,429
AudioPlaySdWav           playSdRaw1;     //xy=278,158
AudioFilterStateVariable filter1;        //xy=289,544
AudioPlaySdWav           playSdRaw4;     //xy=405,309
AudioPlaySdWav           playSdRaw5;     //xy=406,361
AudioPlaySdWav           playSdRaw3;     //xy=409,264
AudioPlaySdWav           playSdRaw2;     //xy=410,227
AudioEffectBitcrusher    bitcrusher1;    //xy=452,120
AudioEffectDelay         delay1;         //xy=528,566
AudioMixer4              mixer3;         //xy=645,270
AudioMixer4              mixer7;         //xy=652,412
AudioMixer4              mixer2;         //xy=838,416
AudioMixer4              mixer1;         //xy=860,302
AudioOutputTDM           tdm3;           //xy=1147,355
AudioConnection          patchCord1(playSdRaw6, 0, filter1, 0);
AudioConnection          patchCord2(playSdRaw1, 0, bitcrusher1, 0);
AudioConnection          patchCord3(filter1, 1, mixer7, 1);
AudioConnection          patchCord4(filter1, 2, delay1, 0);
AudioConnection          patchCord5(playSdRaw4, 0, mixer3, 3);
AudioConnection          patchCord6(playSdRaw5, 0, mixer1, 1);
AudioConnection          patchCord7(playSdRaw5, 1, mixer2, 2);
AudioConnection          patchCord8(playSdRaw3, 0, mixer3, 2);
AudioConnection          patchCord9(playSdRaw2, 0, mixer3, 1);
AudioConnection          patchCord10(bitcrusher1, 0, mixer3, 0);
AudioConnection          patchCord11(delay1, 1, mixer7, 2);
AudioConnection          patchCord12(mixer3, 0, mixer1, 0);
AudioConnection          patchCord13(mixer3, 0, mixer2, 0);
AudioConnection          patchCord14(mixer7, 0, mixer2, 1);
AudioConnection          patchCord15(mixer2, 0, tdm3, 2);
AudioConnection          patchCord16(mixer2, 0, tdm3, 6);
AudioConnection          patchCord17(mixer2, 0, tdm3, 10);
AudioConnection          patchCord18(mixer2, 0, tdm3, 14);
AudioConnection          patchCord19(mixer1, 0, tdm3, 0);
AudioConnection          patchCord20(mixer1, 0, tdm3, 4);
AudioConnection          patchCord21(mixer1, 0, tdm3, 8);
AudioConnection          patchCord22(mixer1, 0, tdm3, 12);
AudioControlCS42448      cs42448_1;      //xy=853,560
// GUItool: end automatically generated code
// GUItool: end automatically generated code

//                       !               !               !               !      
const char* pattern4x4  = "X...X...X...X...X...X...X...X...X...X...X...X...X...X...X...X..."; 
const char* patternSyn  = "..X...X...X...X...X...X...X...X...X...X...X...X...X...X...X....."; 
const char* patternSnr  = "....x.......x.......x.......x.......x.......x.......x.......x..."; 
const char* patternHat  = "..x...x...x...x...x...x...x...x...x...x...x...x...x...x...x...x."; 

//                       !               !               !               !      
const char* pattern1a = "x...............x...............x...............x.............x."; 
const char* pattern2a = ".xxX.xxX.xxX.xxX.xxX.xxX.xxX.xxX.xxX.xxX.xxX.xxX.xxX.xxX.xxX...."; 
const char* pattern3a = "....x.......x.......x.......x.......x.......x.......x.......x.xx"; 
const char* pattern4a = "..x...x...x...x...x...x...x...x...x...x...x...x...x...x...x...x."; 

//                       !               !               !               !      
const char* pattern1b = "x...x...x...x...x...x...x...x...x...x...x...x...x...x...x...x..."; 
const char* pattern2b = ".x.X.x.X.x.X.x.X.x.X.x.X.x.X.x.X.x.X.x.X.x.X.x.X.x.X.x.X.x.X...."; 
const char* pattern3b = "....x.......x.......x.......x.......x.......x.......x.......x.x."; 
const char* pattern4b = "..............x...............................x................."; 

//                       !       -       !       -        !      -       !       -
const char* pattern1c = "x.........x.....x.........x......x........x.....x.........x....."; 
const char* pattern2c = "..X...X.......X...X...X.......X...X...X.......X...X...X..x.x...."; 
const char* pattern3c = "....x.......x.......x.......x.......x.......x.......x...x....x.."; 
const char* pattern4c = "..............x...............................x................."; 



//                       !       -       !       -        !      -       !       -
const char* xpattern1 = "..........................................................B....."; 
const char* xpattern2 = "..d.........................x......X........x.....C.............";

void readPattern(int channel, int pattern, const char* row, sequencer *sequencer) {
  int index = 0;

  while (row[index] != 0) {
    int notelength = 0;
    switch (row[index]) {
      case 'x' : notelength = 15; break; 
      case 'X' : notelength = 31; break;
      case 'B' : notelength = 63; break;
      case 'C' : notelength = 128; break;             
      case 'd' : notelength = 255; break;        
      default:
        break;
    }

    if (notelength > 0) {
        loopelement *hihat = new loopelement();
        hihat->rate = 1.0f;
        hihat->start_tick = (index * 16);
        hihat->stop_tick = (index * 16) + notelength;
        hihat->channel = channel;
        hihat->loopType = looptypex_none;
        sequencer->addelement(pattern, hihat);
    }
    
    index++;
  }
}

String fxnames[12] = {"FX04.wav", "FX09.wav","FX10.wav","FX12.wav", "FX21.wav", "FX28.wav","FX30.wav","FX34.wav","FX35.wav","FX40.wav","FX42.wav","FX77.wav"}; 

void playSample(AudioPlaySdWav &audio, String s) { 
  if (audio.isPlaying())
    audio.stop();
  
  audio.play(s.c_str());
}

void stopSample(AudioPlaySdWav &audio) {
  if (audio.isPlaying())
    audio.stop();            
}

void triggerAudioEvent(sequencerevent *event, AudioPlaySdWav &audio, String filename) {
  if (event->isNoteStartEvent) {
    playSample(audio, filename);
  } else 
    stopSample(audio);
}

void setup() {
  AudioMemory(80);
  Serial.begin(9600);    
  
  if (!(SD.begin(BUILTIN_SDCARD))) {
      // stop here if no SD card, but print a message
      while (1) {
          Serial.println("Unable to access the SD card");
          delay(500);
      }
  }

  AudioNoInterrupts();  // disable audio library momentarily
  // put your setup code here, to run once:
  //cs42448_1.setAddress(0);
  cs42448_1.enable();
  cs42448_1.volume(1);
  //cs42448_1.inputLevel(1);
  AudioInterrupts();   

  bitcrusher1.bits(8);

  sequencer *sequencer = multisequencer.newSequencer();
  
  sequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 1: triggerAudioEvent(event, playSdRaw1, "BASS.WAV"); break;
        case 2: triggerAudioEvent(event, playSdRaw2, "KICK.WAV"); break;
        case 3: triggerAudioEvent(event, playSdRaw3, "SNARE.WAV"); break;
        case 4: triggerAudioEvent(event, playSdRaw4, "Hihat.WAV"); break;
        case 5: triggerAudioEvent(event, playSdRaw5, "BASSSLID.WAV"); break;      
        case 0:
          int r = random(11); 
          triggerAudioEvent(event, playSdRaw6, fxnames[r]); break;

        default:
          break;
      }
  };

  int pattern = 0;

  sequencer->addPattern();
  readPattern(0, pattern, xpattern2, sequencer); //FX
  readPattern(5, pattern, xpattern1, sequencer); //Bassslide
  pattern++;
  
  sequencer->addPattern();
  readPattern(2, pattern, pattern4x4, sequencer); //kick
  readPattern(0, pattern, xpattern2, sequencer); //FX
  readPattern(5, pattern, xpattern1, sequencer); //Bassslide
  pattern++;
  
  sequencer->addPattern();
  readPattern(2, pattern, pattern4x4, sequencer); //kick
  readPattern(1, pattern, patternSyn, sequencer); //bass
  readPattern(0, pattern, xpattern2, sequencer); //FX
  readPattern(5, pattern, xpattern1, sequencer); //Bassslide
  pattern++;
  
  sequencer->addPattern();
  readPattern(2, pattern, pattern4x4, sequencer); //kick
  readPattern(1, pattern, patternSyn, sequencer); //bass
  readPattern(3, pattern, patternSnr, sequencer); //snare
  readPattern(0, pattern, xpattern2, sequencer); //FX
  readPattern(5, pattern, xpattern1, sequencer); //Bassslide
  pattern++;
    
  sequencer->addPattern();
  readPattern(2, pattern, pattern4x4, sequencer); //kick
  readPattern(1, pattern, patternSyn, sequencer); //bass
  readPattern(4, pattern, patternHat, sequencer); //hihat
  readPattern(3, pattern, patternSnr, sequencer); //snare
  readPattern(0, pattern, xpattern2, sequencer); //FX
  readPattern(5, pattern, xpattern1, sequencer); //Bassslide
  pattern++;
  
  // Pattern 2:
  sequencer->addPattern();
  readPattern(2, pattern, pattern1a, sequencer); // kick
  readPattern(3, pattern, pattern3a, sequencer); // snare
  readPattern(1, pattern, pattern2a, sequencer); // bass
  readPattern(4, pattern, pattern4a, sequencer); // hihat
  readPattern(0, pattern, xpattern2, sequencer); //FX
  readPattern(5, pattern, xpattern1, sequencer); //Bassslide
  pattern++;
    
  // Pattern 3:
  sequencer->addPattern();
  readPattern(2, pattern, pattern1b, sequencer); // kick
  readPattern(3, pattern, pattern3b, sequencer); // snare
  readPattern(1, pattern, pattern2b, sequencer); // bass
  readPattern(4, pattern, pattern4b, sequencer); // hihat
  readPattern(0, pattern, xpattern2, sequencer); //FX
  readPattern(5, pattern, xpattern1, sequencer); //Bassslide
  pattern++;
    
  // Pattern 4:
  sequencer->addPattern();
  readPattern(2, pattern, pattern1c, sequencer); // kick
  readPattern(3, pattern, pattern3c, sequencer); // snare
  readPattern(1, pattern, pattern2c, sequencer); // bass
  readPattern(4, pattern, pattern4c, sequencer); // hihat
  readPattern(0, pattern, xpattern2, sequencer); //FX
  readPattern(5, pattern, xpattern1, sequencer); //Bassslide
  pattern++;
    
  multisequencer.start(millis());
}
int count = 0;

String inString = ""; 

void loop() {
  // put your main code here, to run repeatedly:
  multisequencer.tick(millis());
  
  count++;
  if (count > 100000) {
    //sequencer.writescore(0);
    //
    count = 0;
  }
/*
  while (Serial.available()) {
    char inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    if (inChar == '\n') {
      Serial.printf("setting next patteren to %d\n", inString.toInt());
      sequencer.setNextPattern(inString.toInt());
      sequencer.writescore(inString.toInt());
      inString = "";
    }
  }
  */
}

unsigned __exidx_start;
unsigned __exidx_end;
