#include <Audio.h>
#include <SPI.h>
#include <SD.h>

#include "common/sequencer.h"
#include "common/songposition.h"
#include "common/tempo.h"
#include "common/looptype.h"
#include <USBHost_t36.h>

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);

tempo tempo(132.0f);

multisequencer multisequencer(tempo);

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdRaw1;     //xy=278,158
AudioPlaySdWav           playSdRaw5;     //xy=310,372
AudioPlaySdWav           playSdRaw6;     //xy=333,438
AudioPlaySdWav           playSdRaw4;     //xy=405,309
AudioPlaySdWav           playSdRaw3;     //xy=409,264
AudioPlaySdWav           playSdRaw2;     //xy=410,227
AudioEffectBitcrusher    bitcrusher1;    //xy=452,120
AudioMixer4              mixer7;         //xy=634,368
AudioMixer4              mixer3;         //xy=645,270
AudioMixer4              mixer2;         //xy=838,416
AudioMixer4              mixer1;         //xy=860,302
AudioOutputTDM           tdm3;           //xy=1147,355
AudioConnection          patchCord1(playSdRaw1, 0, bitcrusher1, 0);
AudioConnection          patchCord2(playSdRaw5, 0, mixer7, 0);
AudioConnection          patchCord3(playSdRaw6, 0, mixer7, 2);
AudioConnection          patchCord4(playSdRaw4, 0, mixer3, 3);
AudioConnection          patchCord5(playSdRaw3, 0, mixer3, 2);
AudioConnection          patchCord6(playSdRaw2, 0, mixer3, 1);
AudioConnection          patchCord7(bitcrusher1, 0, mixer3, 0);
AudioConnection          patchCord8(mixer7, 0, mixer1, 2);
AudioConnection          patchCord9(mixer7, 0, mixer2, 1);
AudioConnection          patchCord10(mixer3, 0, mixer1, 0);
AudioConnection          patchCord11(mixer3, 0, mixer2, 0);
AudioConnection          patchCord12(mixer2, 0, tdm3, 2);
AudioConnection          patchCord13(mixer2, 0, tdm3, 6);
AudioConnection          patchCord14(mixer2, 0, tdm3, 10);
AudioConnection          patchCord15(mixer2, 0, tdm3, 14);
AudioConnection          patchCord16(mixer1, 0, tdm3, 0);
AudioConnection          patchCord17(mixer1, 0, tdm3, 4);
AudioConnection          patchCord18(mixer1, 0, tdm3, 8);
AudioConnection          patchCord19(mixer1, 0, tdm3, 12);
AudioControlCS42448      cs42448_1;      //xy=853,560
// GUItool: end automatically generated code

//                       !               !               !               !      
const char* pattern4x4 = "X...X...X...X...X...X...X...X...X...X...X...X...X...X...X...X..."; 
const char* patternSyn = "..X...X...X...X...X...X...X...X...X...X...X...X...X...X...X...X."; 
const char* patternSnr = "....x.......x.......x.......x.......x.......x.......x.......x..."; 
const char* patternHat = "..x...x...x...x...x...x...x...x...x...x...x...x...x...x...x...x."; 
const char* pattern8x4 = "x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x."; 
const char* pattern164 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; 
const char* pattern3x4 = ".xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx"; 

//                         !               !               !               !      
const char* pathalf4x4 = "X.......X.......X.......X.......X.......X.......X.......X......."; 
const char* pathalfSyn = "....X.......X.......X.......X.......X.......X.......X.......X...";

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
const char* xpattern0 = "..X...X...X...X...X...X...X...X...X...X...X...X...X...X......X.."; 
const char* xpattern1 = "..........................................................B....."; 
const char* xpattern2 = "..d.................................B...............C...........";

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

String fxnames[14] = {"FX04.wav", "FX09.wav","FX10.wav","FX12.wav", "FX21.wav", "FX28.wav","FX30.wav","FX34.wav","FX35.wav","FX40.wav","FX42.wav","FX77.wav", "HIT1.wav", "HIT2.wav"}; 
String bassslidenames[11] = {"BASSSL01.wav", "BASSSL02.wav","BASSSL03.wav","BASSSL04.wav", "BASSSL05.wav", "BASSSL06.wav","BASSSL07.wav","BASSSL08.wav","BASSSL09.wav","BASSSL10.wav","BASSSL11.wav"}; 


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


sequencer *beatsequencer;
sequencer *hatsequencer;
sequencer *basssequencer;
sequencer *fxsequencer;

void setup() {
  AudioNoInterrupts();  // disable audio library momentarily
  AudioMemory(80);
  Serial.begin(9600);    
  
  if (!(SD.begin(BUILTIN_SDCARD))) {
      // stop here if no SD card, but print a message
      while (1) {
          Serial.println("Unable to access the SD card");
          delay(500);
      }
  }

  myusb.begin();
  midi1.setHandleNoteOn(myNoteOn);
  midi1.setHandleNoteOff(myNoteOff);
  midi1.setHandleControlChange(myControlChange);
  
  // put your setup code here, to run once:
  //cs42448_1.setAddress(0);
  cs42448_1.enable();
  cs42448_1.volume(1);
  //cs42448_1.inputLevel(1);
  AudioInterrupts();   

  bitcrusher1.bits(16);

  while (!midi1) {
    Serial.printf("waiting for akai APC40...\n");
    delay(100);
  }
  // turn off all leds on the akai AP40
  for (int j=0; j<8;j++)
    for (int i=0; i<5;i++)
      midi1.sendNoteOff(53+i, 0, j+1);

  multisequencer.onloopchange = [&] (long channel, long pattern) {
    Serial.printf("channel %d, pattern changed to %d\n", channel, pattern);
    for (int i=0; i<5;i++)
      midi1.sendNoteOff(53+i, 0, channel+1);

    midi1.sendNoteOn(53 + pattern, 1, channel+1);  // green
  };

  beatsequencer = multisequencer.newSequencer();
  hatsequencer = multisequencer.newSequencer();
  basssequencer = multisequencer.newSequencer();
  fxsequencer = multisequencer.newSequencer();

  beatsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: triggerAudioEvent(event, playSdRaw1, "KICK.WAV"); break;
        case 1: triggerAudioEvent(event, playSdRaw2, "SNARE.WAV"); break;      
        default: break;
      }
  };

  hatsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: triggerAudioEvent(event, playSdRaw4, "Hihat.WAV"); break;
        default: break;
      }
  };

  basssequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: triggerAudioEvent(event, playSdRaw1, "BASS.WAV"); break;
        case 1: 
          int r = random(10); 
          triggerAudioEvent(event, playSdRaw6, bassslidenames[r]); break;
        default: break;
      }
  };

  fxsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) { 
        case 0:
          int r = random(13); 
          triggerAudioEvent(event, playSdRaw6, fxnames[r]); break;

        default: break;
      }
  };

  int pattern = 0;
  
  // beatsequencer
  pattern = beatsequencer->addPattern(4); // no beat
  
  pattern = beatsequencer->addPattern(4); // kick solo 4 x 4
  readPattern(0, pattern, pattern4x4, beatsequencer); //kick

  pattern = beatsequencer->addPattern(4); // kick solo 4 x 4 + snare
  readPattern(0, pattern, pattern4x4, beatsequencer); //kick
  readPattern(1, pattern, patternSnr, beatsequencer); //snare

  pattern = beatsequencer->addPattern(4); // breakbeat
  readPattern(0, pattern, pattern1c, beatsequencer); //kick
  readPattern(1, pattern, patternSnr, beatsequencer); //snare
  pattern++;

  pattern = beatsequencer->addPattern(4); // half-time
  readPattern(0, pattern, pathalf4x4, beatsequencer); //kick
  readPattern(1, pattern, pathalfSyn, beatsequencer); //snare
  pattern++;

  pattern = beatsequencer->addPattern(4); // snare solo
  readPattern(1, pattern, patternSnr, beatsequencer); //snare

  
  
  // hatsequencer
  pattern = hatsequencer->addPattern(4); // no hats

  pattern = hatsequencer->addPattern(4);
  readPattern(0, pattern, patternSyn, hatsequencer); // syncopated
  
  pattern = hatsequencer->addPattern(4);
  readPattern(0, pattern, pattern8x4, hatsequencer); // 8 x 4

  pattern = hatsequencer->addPattern(4);
  readPattern(0, pattern, pattern164, hatsequencer); // 16 x 4

  pattern = hatsequencer->addPattern(4);
  readPattern(0, pattern, pathalf4x4, hatsequencer); // 4 x 4

  pattern = hatsequencer->addPattern(4);
  readPattern(0, pattern, pattern3x4, hatsequencer); // 3 x 4

 
  // basssequencer
  pattern = basssequencer->addPattern(4); // no bass

  pattern = basssequencer->addPattern(4); // syncopated
  readPattern(0, pattern, patternSyn, basssequencer); // bass

  pattern = basssequencer->addPattern(4); // syncopated, with last as slide
  readPattern(0, pattern, xpattern0, basssequencer); // 3 x 4
  readPattern(1, pattern, xpattern1, basssequencer); 
  
  pattern = basssequencer->addPattern(4); // syncopated, with last as slide
  readPattern(0, pattern, pattern2a, basssequencer); // .xxx.xxx.xxx.xxx
  readPattern(1, pattern, xpattern1, basssequencer); 



  //fxsequencer
  pattern = fxsequencer->addPattern(4); // no fx

  pattern = fxsequencer->addPattern(4); // inbetween fx
  readPattern(0, pattern, xpattern2, fxsequencer); // fx
     

  
  multisequencer.start(millis());
  printusage();
  delay(1000);
}

String inputChannel="", inString = ""; 
bool inputChannelEntered = false;

void loop() {
  myusb.Task();
  midi1.read();
    
  
  // put your main code here, to run repeatedly:
  multisequencer.tick(millis());
  

  while (Serial.available()) {
    char inChar = Serial.read();   
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    if (inChar == '\n') {
      if (inputChannelEntered == false) {
        inputChannel = inString;
        inputChannelEntered = true;
        inString = "";
      } else {

        sequencer *currentSequencer = NULL;
        switch (inputChannel.toInt()) {
          case 0: currentSequencer = beatsequencer; break;
          case 1: currentSequencer = hatsequencer; break;
          case 2: currentSequencer = basssequencer; break;
          case 3: currentSequencer = fxsequencer; break;
          default:
            Serial.printf("invalid channel input (should be 0,1,2,3): %s\n", inputChannel);
            break;
        } 
              
        if (currentSequencer != NULL) {
          Serial.printf("setting next patteren to %d\n", inString.toInt());
          currentSequencer->setNextPattern(inString.toInt());
          currentSequencer->writescore(inString.toInt());
        }
        inString = "";
        inputChannel = "";    
        inputChannelEntered = false; 
        printusage();
      }
    }
  }

}


void myNoteOn(byte channel, byte note, byte velocity) {
  // When a USB device with multiple virtual cables is used,
  // midi1.getCable() can be used to read which of the virtual
  // MIDI cables received this message.
  //Serial.print("Note On, ch=");
  //Serial.print(channel, DEC);
  //Serial.print(", note=");
  //Serial.print(note, DEC);
  //Serial.print(", velocity=");
  //Serial.println(velocity, DEC);

  sequencer *sequencer = NULL;
  switch (channel) {
    case 1: sequencer = beatsequencer; break;
    case 2: sequencer = hatsequencer; break;
    case 3: sequencer = basssequencer; break;
    case 4: sequencer = fxsequencer; break;
    default: break;
  }

  if (sequencer != NULL) {
    Serial.printf("set next pattern: %d - channel: %d\n", note - 53, channel);
     sequencer->setNextPattern(note - 53);
  }
}

void myNoteOff(byte channel, byte note, byte velocity) {
  Serial.print("Note Off, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);

  midi1.sendNoteOn(note, 2, channel);
}

void myControlChange(byte channel, byte control, byte value) {
  
  Serial.print("Control Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", control=");
  Serial.print(control, DEC);
  Serial.print(", value=");
  Serial.println(value, DEC);

  if (control == 48) {
    float newBPM = 100.0f + value/2.0f;
    Serial.printf("BPM: %f\n",newBPM);
    tempo.setBeatsPerMinute(newBPM);
  }
}

void akaiLED(byte channel, byte pattern, bool on) {
  midi1.sendNoteOn(53+pattern, (on)? 127 : 0, channel);
}

void printusage() {
  Serial.printf("--------------\n");
  Serial.printf("0: kick and snare (0..5)\n");
  Serial.printf("\t\t0:off\t\t1:kick\t\t2:kick+snare\t\t3:breakbeat\t\t4:halftime\t\t5:snare only\n");
  Serial.printf("1: hihats (0..5)\n");
  Serial.printf("\t\t0:off\t\t1:sync\t\t2:8\t\t\t3:16\t\t\t4:4x4\t\t\t5:.xxx\n");
  Serial.printf("2: bass (0..3)\n");
  Serial.printf("\t\t0:off\t\t1:sync\t\t2:w/slide\t\t3:.xxx\n");
  Serial.printf("3: effects(0..1)\n");
  Serial.printf("\t\t0:off\t\t1:fx\n");
}

unsigned __exidx_start;
unsigned __exidx_end;
