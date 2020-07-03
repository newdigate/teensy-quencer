#include <Audio.h>
#include <SPI.h>
#include <SD.h>

#include "common/sequencer.h"
#include "common/songposition.h"
#include "common/tempo.h"
#include "common/looptype.h"

tempo tempo(132.0f);

songposition position;

sequencer sequencer(tempo, position);

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdRaw1;     //xy=211,106
AudioPlaySdWav           playSdRaw2;     //xy=211,143
AudioPlaySdWav           playSdRaw3;     //xy=209,178
AudioPlaySdWav           playSdRaw5;     //xy=209,285
AudioPlaySdWav           playSdRaw6;     //xy=209,326
AudioPlaySdWav           playSdRaw4;     //xy=210,217
AudioMixer4              mixer5;         //xy=486,295
AudioMixer4              mixer6;         //xy=491,410
AudioMixer4              mixer4;         //xy=512,204
AudioMixer4              mixer3;         //xy=515,102
AudioMixer4              mixer1;         //xy=699,135
AudioMixer4              mixer2;         //xy=701,284
AudioOutputTDM           tdm3;           //xy=920,195
AudioConnection          patchCord9(playSdRaw1, 0, mixer3, 0);
AudioConnection          patchCord10(playSdRaw1, 1, mixer4, 0);
AudioConnection          patchCord11(playSdRaw2, 0, mixer3, 1);
AudioConnection          patchCord12(playSdRaw2, 1, mixer4, 1);
AudioConnection          patchCord3(playSdRaw3, 0, mixer5, 0);
AudioConnection          patchCord4(playSdRaw3, 1, mixer6, 0);
AudioConnection          patchCord5(playSdRaw4, 0, mixer5, 1);
AudioConnection          patchCord6(playSdRaw4, 1, mixer6, 1);
AudioConnection          patchCord1(playSdRaw5, 0, mixer3, 2);
AudioConnection          patchCord2(playSdRaw5, 1, mixer4, 2);
AudioConnection          patchCord7(playSdRaw6, 0, mixer3, 3);
AudioConnection          patchCord8(playSdRaw6, 1, mixer4, 3);
AudioConnection          patchCord13(mixer5, 0, mixer1, 1);
AudioConnection          patchCord14(mixer6, 0, mixer2, 1);
AudioConnection          patchCord15(mixer4, 0, mixer2, 0);
AudioConnection          patchCord16(mixer3, 0, mixer1, 0);
AudioConnection          patchCord17(mixer1, 0, tdm3, 0);
AudioConnection          patchCord18(mixer1, 0, tdm3, 4);
AudioConnection          patchCord19(mixer1, 0, tdm3, 8);
AudioConnection          patchCord20(mixer1, 0, tdm3, 12);
AudioConnection          patchCord21(mixer2, 0, tdm3, 2);
AudioConnection          patchCord22(mixer2, 0, tdm3, 6);
AudioConnection          patchCord23(mixer2, 0, tdm3, 10);
AudioConnection          patchCord24(mixer2, 0, tdm3, 14);
AudioControlCS42448      cs42448_1;      //xy=652,431
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
const char* xpattern1 = "............................................................B..."; 
const char* xpattern2 = "..C.........................x......x........x.....x.............";

void readPattern(int channel, int pattern, const char* row) {
  int index = 0;

  while (row[index] != 0) {
    int notelength = 0;
    switch (row[index]) {
      case 'x' : notelength = 15; break; 
      case 'X' : notelength = 31; break;
      case 'B' : notelength = 63; break;
      case 'C' : notelength = 128; break;                
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
        sequencer.addelement(pattern, hihat);
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

  sequencer.onevent = [] (sequencerevent *event) {
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

  
  sequencer.addPattern();
  readPattern(2, 0, pattern4x4); //kick
  readPattern(0, 0, xpattern2); //FX
  readPattern(5, 0, xpattern1); //Bassslide
  
  sequencer.addPattern();
  readPattern(2, 1, pattern4x4); //kick
  readPattern(1, 1, patternSyn); //bass
  readPattern(0, 1, xpattern2); //FX
  readPattern(5, 1, xpattern1); //Bassslide
  
  sequencer.addPattern();
  readPattern(2, 2, pattern4x4); //kick
  readPattern(1, 2, patternSyn); //bass
  readPattern(3, 2, patternSnr); //snare
  readPattern(0, 2, xpattern2); //FX
  readPattern(5, 2, xpattern1); //Bassslide
  
  sequencer.addPattern();
  readPattern(2, 3, pattern4x4); //kick
  readPattern(1, 3, patternSyn); //bass
  readPattern(4, 3, patternHat); //hihat
  readPattern(3, 3, patternSnr); //snare
  readPattern(0, 3, xpattern2); //FX
  readPattern(5, 3, xpattern1); //Bassslide
  
  // Pattern 2:
  sequencer.addPattern();
  readPattern(2, 4, pattern1a); // kick
  readPattern(3, 4, pattern3a); // snare
  readPattern(1, 4, pattern2a); // bass
  readPattern(4, 4, pattern4a); // hihat
  readPattern(0, 4, xpattern2); //FX
  readPattern(5, 4, xpattern1); //Bassslide
  // Pattern 3:
  sequencer.addPattern();
  readPattern(2, 5, pattern1b); // kick
  readPattern(3, 5, pattern3b); // snare
  readPattern(1, 5, pattern2b); // bass
  readPattern(4, 5, pattern4b); // hihat
  readPattern(0, 5, xpattern2); //FX
  readPattern(5, 5, xpattern1); //Bassslide
  // Pattern 4:
  sequencer.addPattern();
  readPattern(2, 6, pattern1c); // kick
  readPattern(3, 6, pattern3c); // snare
  readPattern(1, 6, pattern2c); // bass
  readPattern(4, 6, pattern4c); // hihat
  readPattern(0, 6, xpattern2); //FX
  readPattern(5, 6, xpattern1); //Bassslide
  
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
int count = 0;

String inString = ""; 

void loop() {
  // put your main code here, to run repeatedly:
  sequencer.tick(millis());
  
  count++;
  if (count > 100000) {
    //sequencer.writescore(0);
    //
    count = 0;
  }

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
}

unsigned __exidx_start;
unsigned __exidx_end;
