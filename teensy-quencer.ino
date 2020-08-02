#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <teensy_sampler.h>
#include "src/sequencer.h"
#include "src/songposition.h"
#include "src/tempo.h"
#include "src/looptype.h"
#include "src/midireader.h"
#include "src/midisequenceadapter.h"
#include <USBHost_t36.h>

#include <Adafruit_GFX.h>    // Core graphics library
#include <ST7735_t3.h> // Hardware-specific library
#define TFT_CS   6  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    2  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   0 // RST can use any pin
ST7735_t3 tft = ST7735_t3(TFT_CS, TFT_DC, TFT_RST);

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);
MIDIDevice midi2(myusb);

tempo tempo(132.0f);
multisequencer multisequencer(tempo);
midisequenceadapter adapter(multisequencer);

// GUItool: begin automatically generated code
AudioPlaySdWavResmp           playSdRaw7;     //xy=184,479
AudioPlaySdWavResmp           playSdRaw6;     //xy=188,417
AudioPlaySdWavResmp           playSdRaw8;     //xy=189,534
AudioPlaySdWavResmp           playSdRaw5;     //xy=193,359
AudioPlaySdWavResmp           playSdRaw3;     //xy=195,254
AudioPlaySdWavResmp           playSdRaw4;     //xy=195,306
AudioPlaySdWavResmp           playSdRaw2;     //xy=199,200
AudioPlaySdWavResmp           playSdRaw1;     //xy=201,150
AudioMixer4              mixer7;         //xy=430,390
AudioMixer4              mixer3;         //xy=432,316
AudioInputTDM            tdm1;           //xy=567,375
AudioMixer4              mixer1;         //xy=568,218
AudioMixer4              mixer2;         //xy=571,535
AudioMixer4              mixer4;         //xy=780,101
AudioMixer4              mixer10;        //xy=779,552
AudioMixer4              mixer6;         //xy=782,162
AudioMixer4              mixer9;         //xy=782,223
AudioMixer4              mixer8;         //xy=781,487
AudioMixer4              mixer11;        //xy=782,284
AudioMixer4              mixer5;         //xy=783,423
AudioMixer4              mixer12;        //xy=786,616
AudioOutputTDM           tdm3;           //xy=985,399
AudioConnection          patchCord1(playSdRaw7, 0, mixer7, 3);
AudioConnection          patchCord2(playSdRaw7, 1, mixer7, 0);
AudioConnection          patchCord3(playSdRaw6, 0, mixer7, 2);
AudioConnection          patchCord4(playSdRaw8, 0, mixer1, 1);
AudioConnection          patchCord5(playSdRaw8, 1, mixer2, 2);
AudioConnection          patchCord6(playSdRaw5, 0, mixer7, 1);
AudioConnection          patchCord7(playSdRaw3, 0, mixer3, 2);
AudioConnection          patchCord8(playSdRaw4, 0, mixer3, 3);
AudioConnection          patchCord9(playSdRaw2, 0, mixer3, 1);
AudioConnection          patchCord10(playSdRaw1, 0, mixer3, 0);
AudioConnection          patchCord11(mixer7, 0, mixer1, 2);
AudioConnection          patchCord12(mixer7, 0, mixer2, 1);
AudioConnection          patchCord13(mixer3, 0, mixer1, 0);
AudioConnection          patchCord14(mixer3, 0, mixer2, 0);
AudioConnection          patchCord15(tdm1, 0, mixer4, 1);
AudioConnection          patchCord16(tdm1, 2, mixer5, 0);
AudioConnection          patchCord17(tdm1, 4, mixer6, 0);
AudioConnection          patchCord18(tdm1, 6, mixer8, 0);
AudioConnection          patchCord19(tdm1, 8, mixer9, 0);
AudioConnection          patchCord20(tdm1, 10, mixer10, 0);
AudioConnection          patchCord21(tdm1, 12, mixer11, 0);
AudioConnection          patchCord22(tdm1, 14, mixer12, 0);
AudioConnection          patchCord23(mixer1, 0, mixer4, 0);
AudioConnection          patchCord24(mixer1, 0, mixer6, 1);
AudioConnection          patchCord25(mixer1, 0, mixer9, 1);
AudioConnection          patchCord26(mixer1, 0, mixer11, 1);
AudioConnection          patchCord27(mixer2, 0, mixer5, 1);
AudioConnection          patchCord28(mixer2, 0, mixer8, 1);
AudioConnection          patchCord29(mixer2, 0, mixer10, 1);
AudioConnection          patchCord30(mixer2, 0, mixer12, 1);
AudioConnection          patchCord31(mixer4, 0, tdm3, 0);
AudioConnection          patchCord32(mixer10, 0, tdm3, 10);
AudioConnection          patchCord33(mixer6, 0, tdm3, 4);
AudioConnection          patchCord34(mixer9, 0, tdm3, 8);
AudioConnection          patchCord35(mixer8, 0, tdm3, 6);
AudioConnection          patchCord36(mixer11, 0, tdm3, 12);
AudioConnection          patchCord37(mixer5, 0, tdm3, 2);
AudioConnection          patchCord38(mixer12, 0, tdm3, 14);
AudioControlCS42448      cs42448_1;      //xy=569,637
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

//                       !   .   -   .   !sss.sss-sss.sss!sss.sss-sss.sss!sss.sss-sss.sss
const char* pattern1c = "x.........x.....x.........x.....x.........x.....x.........x....."; 
const char* pattern2c = "..X...X.......X...X...X.......X...X...X.......X...X...X..x.x...."; 
const char* pattern3c = "....x.......x.......x.......x.......x.......x.......x.......x..."; 
const char* pattern4c = "..............x...............................x................."; 



//                       !       -       !       -        !      -       !       -
const char* xpattern0 = "..X...X...X...X...X...X...X...X...X...X...X...X...X...X......X.."; 
const char* xpattern1 = "..........................................................B....."; 
const char* xpattern2 = "..C.............................................................";
const char* xpattern3 = "Q...............................................................";
const char* xpattern4 = "Q...............................................................";

//                       !'''+'''-'''+'''!'''+'''-'''+'''!'''+'''-'''+'''!'''+'''-'''+'''!
const char* xpattern5 = "c.c#d.d#e.f.f#g.g#a.a#b.........c.c#d.d#e.f.f#g.g#a.a#b.........";

double calcPitchFactor(uint8_t note) {
    double result = pow(2.0, (note-60) / 12.0);
    return result;
}

void readPattern(int channel, int pattern, const char* row, sequencer *sequencer) {
  int index = 0;

    while (row[index] != 0) {
        char nextNote = index < strlen(row) - 1? row[index + 1] : '\0';
        int notelength = 0;
        double pitchFactor = 1.0;
        switch (row[index]) {
            case 'x' : notelength = 15; break;
            case 'X' : notelength = 31; break;
            case 'B' : notelength = 63; break;
            case 'C' : notelength = 128; break;
            case 'Q' : notelength = 4095; break;

            case 'c': pitchFactor = (nextNote == '#')? calcPitchFactor(61) : 1.0; notelength = 15; break;
            case 'd': pitchFactor = (nextNote == '#')? calcPitchFactor(63) : calcPitchFactor(62); notelength = 15; break;
            case 'e': pitchFactor = calcPitchFactor(64); notelength = 15; break;
            case 'f': pitchFactor = (nextNote == '#')? calcPitchFactor(66) : calcPitchFactor(65); notelength = 15; break;
            case 'g': pitchFactor = (nextNote == '#')? calcPitchFactor(68) : calcPitchFactor(67); notelength = 15; break;
            case 'a': pitchFactor = (nextNote == '#')? calcPitchFactor(70) : calcPitchFactor(69); notelength = 15; break;
            case 'b': pitchFactor = calcPitchFactor(71); notelength = 15; break;

            default:
            break;
        }

    if (notelength > 0) {
        loopelement *hihat = new loopelement();
        hihat->rate = 1.0f;
        hihat->start_tick = (index * 480 / 4);
        hihat->stop_tick = (index * 480 / 4) + (notelength * 8) ;
        hihat->channel = channel;
        hihat->loopType = looptypex_none;
        hihat->rate = pitchFactor;
        sequencer->addelement(pattern, hihat);
    }
    
    index++;
  }
}

String longfxnames[2] = {"LONGFX01.wav", "LONGFX02.wav"}; 
String fxnames[18] = {"FX01.wav", "FX02.wav", "FX03.wav", "FX04.wav", "FX05.wav", "FX06.wav", "FX07.wav", "FX09.wav","FX10.wav", "FX21.wav", "FX28.wav","FX30.wav","FX34.wav","FX35.wav","FX40.wav","FX77.wav", "HIT1.wav", "HIT2.wav"}; 
String bassslidenames[11] = {"BASSSL01.wav", "BASSSL02.wav","BASSSL03.wav","BASSSL04.wav", "BASSSL05.wav", "BASSSL06.wav","BASSSL07.wav","BASSSL08.wav","BASSSL09.wav","BASSSL10.wav","BASSSL11.wav"}; 


void playSample(AudioPlaySdWavResmp &audio, String s, double rate) {
  if (audio.isPlaying())
    audio.stop();
  audio.setPlaybackRate(rate);
  audio.play(s.c_str());
}

void stopSample(AudioPlaySdWavResmp &audio) {
  if (audio.isPlaying())
    audio.stop();            
}

void triggerAudioEvent(sequencerevent *event, AudioPlaySdWavResmp &audio, String filename) {
  if (event->isNoteStartEvent) {
    playSample(audio, filename, event->rate);
  } else 
    stopSample(audio);
}


sequencer *beatsequencer;
sequencer *snaresequencer;
sequencer *hatsequencer;
sequencer *basssequencer;
sequencer *fxsequencer;
sequencer *crashsequencer;
sequencer *longfxsequencer;

void setup() {
  AudioNoInterrupts();  // disable audio library momentarily
  AudioMemory(60);

  SPI.begin();
  tft.initR(INITR_GREENTAB);
  tft.setRotation(3);
  
  tft.fillScreen(ST7735_BLACK);
  tft.println("init..."); 
  
  Serial.begin(9600);    
  
  while (!(SD.begin(BUILTIN_SDCARD))) {
      // stop here if no SD card, but print a message
        tft.fillScreen(ST7735_BLACK);
        tft.setCursor(0,0);
        tft.println("Unable to access the SD card");
        Serial.println("Unable to access the SD card");
        delay(1000);
  }

  myusb.begin();
  midi1.setHandleNoteOn(myNoteOn);
  midi1.setHandleNoteOff(myNoteOff);
  midi1.setHandleControlChange(myControlChange);

  midi2.setHandleNoteOn(myNoteOn);
  midi2.setHandleNoteOff(myNoteOff);
  midi2.setHandleControlChange(myControlChange);
  
  // put your setup code here, to run once:
  //cs42448_1.setAddress(0);
  cs42448_1.enable();
  cs42448_1.volume(1);
  //cs42448_1.inputLevel(1);
  AudioInterrupts();   

  while (!midi1) {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0,0);
    tft.println("waiting for akai APC40...");
    Serial.println("waiting for akai APC40...");
    delay(1000);
  }
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0,0);
  tft.println("connected to APC40...");
    
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
  snaresequencer = multisequencer.newSequencer();
  hatsequencer = multisequencer.newSequencer();
  basssequencer = multisequencer.newSequencer();
  fxsequencer = multisequencer.newSequencer();
  crashsequencer = multisequencer.newSequencer();
  longfxsequencer = multisequencer.newSequencer();
  
  beatsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: triggerAudioEvent(event, playSdRaw1, "KICK.WAV"); break;      
        default: break;
      }
  };

  snaresequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: triggerAudioEvent(event, playSdRaw2, "SNARE.WAV"); break;      
        default: break;
      }
  };

  hatsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: triggerAudioEvent(event, playSdRaw3, "Hihat.WAV"); break;
        default: break;
      }
  };

  basssequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: triggerAudioEvent(event, playSdRaw4, "BASS.WAV"); break;
        case 1: 
          int r = random(10); 
          triggerAudioEvent(event, playSdRaw5, bassslidenames[r]); break;
        default: break;
      }
  };

  fxsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) { 
        case 0:
          int r = random(17); 
          triggerAudioEvent(event, playSdRaw6, fxnames[r]); break;

        default: break;
      }
  };

  crashsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) { 
        case 0: triggerAudioEvent(event, playSdRaw7, "CRASH.WAV"); break;
        default: break;
      }
  };

  longfxsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) { 
        case 0:
          int r = random(1); 
          triggerAudioEvent(event, playSdRaw8, longfxnames[r]); break;

        default: break;
      }
  };

  int pattern = 0;
  int currentChannel = 0;
  
  // beatsequencer
  pattern = beatsequencer->addPattern(4); // no beat
  
  pattern = beatsequencer->addPattern(4); // kick solo 4 x 4
  readPattern(0, pattern, pattern4x4, beatsequencer); //kick

  pattern = beatsequencer->addPattern(4); // breakbeat
  readPattern(0, pattern, pattern1c, beatsequencer); //kick
  pattern++;

  pattern = beatsequencer->addPattern(4); // half-time
  readPattern(0, pattern, pathalf4x4, beatsequencer); //kick
  pattern++;


  // snaresequencer
  currentChannel++;
  pattern = beatsequencer->addPattern(4); // no beat 4 bars
  
  adapter.loadMidi("snare.mid");
  adapter.loadMidifileToNextChannelPattern(currentChannel, 0, 8);  // multicequencer channel number, midi track number, 8 bars long
  pattern++;
  
  // hatsequencer
  currentChannel++;
  pattern = hatsequencer->addPattern(4); // no hats

  adapter.loadMidi("hihat.mid");
  adapter.loadMidifileToNextChannelPattern(currentChannel, 0, 8);  // multicequencer channel number, midi track number, 8 bars long
  basssequencer->setNextPattern(pattern);
  pattern++;

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
  currentChannel++;
  pattern = basssequencer->addPattern(4); // no bass

  pattern = basssequencer->addPattern(4); // syncopated
  readPattern(0, pattern, patternSyn, basssequencer); // bass

  pattern = basssequencer->addPattern(4); // syncopated, with last as slide
  readPattern(0, pattern, xpattern0, basssequencer); // 3 x 4
  readPattern(1, pattern, xpattern1, basssequencer); 
  
  pattern = basssequencer->addPattern(4); // pitched frequencies
  readPattern(0, pattern, xpattern5, basssequencer); // .xxx.xxx.xxx.xxx

  adapter.loadMidi("dredbass.mid");
  adapter.loadMidifileToNextChannelPattern(currentChannel, 0, 8, 24);
  pattern++;
  basssequencer->setNextPattern(pattern);


  //fxsequencer
  currentChannel++;
  pattern = fxsequencer->addPattern(4); // no fx

  pattern = fxsequencer->addPattern(4); // inbetween fx
  readPattern(0, pattern, xpattern2, fxsequencer); // fx
     
  //crashsequencer
  currentChannel++;
  pattern = crashsequencer->addPattern(8); // no crash

  pattern = crashsequencer->addPattern(8); // crash on first beat of 8 bars
  readPattern(0, pattern, xpattern3, crashsequencer); // fx

          
  //longfxsequencer
  currentChannel++;
  pattern = longfxsequencer->addPattern(8); // no long fx

  pattern = longfxsequencer->addPattern(8); // longfx on first beat of 16 bars
  readPattern(0, pattern, xpattern4, longfxsequencer); // fx
     
  
  multisequencer.start(micros());
  printusage();
  delay(1000);
}

String inputChannel="", inString = ""; 
bool inputChannelEntered = false;
float oldBPM = 0.0;
float newBPM = 0.0;
long bpmIndicatorTimer = 0;
 
void loop() {
  myusb.Task();
  midi1.read();
  midi2.read();
    
  bpmIndicatorTimer++;
  if (bpmIndicatorTimer == 100000){
    bpmIndicatorTimer = 0;
    
    if (newBPM != oldBPM) {
      tft.setTextColor(ST7735_BLACK);
      tft.setCursor(0,0);
      tft.setTextSize(2);
      tft.printf("BPM:\n%.1f", oldBPM);

      tft.setTextColor(ST7735_RED);          
      tft.setCursor(0,0);
      tft.setTextSize(2);
      tft.printf("BPM:\n%.1f", newBPM);
      oldBPM = newBPM;
    }
  }
  
  // put your main code here, to run repeatedly:
  multisequencer.tick(micros());
  

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
          case 4: currentSequencer = crashsequencer; break;
          case 5: currentSequencer = longfxsequencer; break;
          default:
            Serial.printf("invalid channel input (should be 0..5): %s\n", inputChannel);
            break;
        } 
              
        if (currentSequencer != NULL) {
          Serial.printf("setting next patteren to %d\n", inString.toInt());
          currentSequencer->setNextPattern(inString.toInt());
          currentSequencer->writescore(inString.toInt());
          currentSequencer->writenoteslist(inString.toInt());
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
  Serial.print("Note On, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);

  sequencer *sequencer = NULL;
  switch (channel) {
    case 1: sequencer = beatsequencer; break;
    case 2: sequencer = hatsequencer; break;
    case 3: sequencer = basssequencer; break;
    case 4: sequencer = fxsequencer; break;
    case 5: sequencer = crashsequencer; break;
    case 6: sequencer = longfxsequencer; break;
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
    newBPM = 100.0f + value/2.0f;
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
