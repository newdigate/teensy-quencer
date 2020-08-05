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
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// Number of samples in each delay line
#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
// Allocate the delay lines for left and right channels
short delayline[FLANGE_DELAY_LENGTH];

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdRaw7;     //xy=782.1388702392578,236.66666269302368
AudioPlaySdWav           playSdRaw8;     //xy=783.6944465637207,431.25000381469727

AudioPlaySdWavResmp           playSdRaw6;     //xy=411.50000762939453,473.25000953674316
AudioPlaySdWavResmp           playSdRaw3;     //xy=421.00000762939453,319.5000047683716
AudioPlaySdWavResmp           playSdRaw2;     //xy=429.25000762939453,240.50000381469727
AudioPlaySdWavResmp           playSdRaw4;     //xy=431.00000762939453,363.2500057220459
AudioPlaySdWavResmp           playSdRaw5;     //xy=432.00000762939453,423.5000057220459
AudioPlaySdWavResmp           playSdRaw1;     //xy=435.25000762939453,169.25000095367432

// GUItool: begin automatically generated code
AudioSynthKarplusStrong  string1;        //xy=55,624.7421112060547
AudioEffectReverb        reverb1;        //xy=162.22220611572266,570.0001711845398
AudioMixer4              mixer13;        //xy=288.8888969421387,631.1109943389893
AudioSynthWaveformSine   sine1;          //xy=412.00000762939453,547.2500095367432
AudioEffectBitcrusher    bitcrusher1;    //xy=433.3332920074463,650.000072479248
AudioEffectEnvelope      envelope8;      //xy=442.49988555908203,597.2024974822998
AudioEffectEnvelope      envelope3;      //xy=586.7500076293945,311.75000286102295
AudioEffectEnvelope      envelope2;      //xy=588.7500076293945,234.75000095367432
AudioEffectEnvelope      envelope4;      //xy=589,357
AudioEffectEnvelope      envelope6;      //xy=590.5,466.25
AudioEffectEnvelope      envelope7;      //xy=592.5,547.25
AudioEffectEnvelope      envelope5;      //xy=596,417
AudioEffectEnvelope      envelope1;      //xy=603.2500076293945,163.50000095367432
AudioEffectFlange        flange1;        //xy=634.4445037841797,596.6667861938477
AudioEffectReverb        reverb2;        //xy=636.6667404174805,649.9999523162842
AudioMixer4              mixer7;         //xy=793.7500038146973,371.5000066757202
AudioMixer4              mixer3;         //xy=795.7500038146973,306.5000066757202
AudioInputTDM            tdm1;           //xy=961.7500038146973,396.5000066757202
AudioMixer4              mixer1;         //xy=962.7500038146973,239.50000667572021
AudioMixer4              mixer15;        //xy=963.7500038146973,175.50000667572021
AudioMixer4              mixer16;        //xy=964.7500038146973,622.5000066757202
AudioMixer4              mixer2;         //xy=965.7500038146973,556.5000066757202
AudioMixer4              mixer4;         //xy=1174.7500038146973,122.50000667572021
AudioMixer4              mixer10;        //xy=1173.7500038146973,573.5000066757202
AudioMixer4              mixer6;         //xy=1176.7500038146973,183.50000667572021
AudioMixer4              mixer9;         //xy=1176.7500038146973,244.50000667572021
AudioMixer4              mixer8;         //xy=1175.7500038146973,508.5000066757202
AudioMixer4              mixer11;        //xy=1176.7500038146973,305.5000066757202
AudioMixer4              mixer5;         //xy=1177.7500038146973,444.5000066757202
AudioMixer4              mixer12;        //xy=1180.7500038146973,637.5000066757202
AudioOutputTDM           tdm3;           //xy=1379.7500038146973,420.5000066757202
AudioConnection          patchCord1(string1, reverb1);
AudioConnection          patchCord2(string1, 0, mixer13, 1);
AudioConnection          patchCord3(reverb1, 0, mixer13, 0);
AudioConnection          patchCord4(mixer13, bitcrusher1);
AudioConnection          patchCord5(playSdRaw6, 0, envelope6, 0);
AudioConnection          patchCord6(sine1, envelope7);
AudioConnection          patchCord7(playSdRaw3, 0, envelope3, 0);
AudioConnection          patchCord8(playSdRaw2, 0, envelope2, 0);
AudioConnection          patchCord9(playSdRaw4, 0, envelope4, 0);
AudioConnection          patchCord10(playSdRaw5, 0, envelope5, 0);
AudioConnection          patchCord11(playSdRaw1, 0, envelope1, 0);
AudioConnection          patchCord12(bitcrusher1, envelope8);
AudioConnection          patchCord13(envelope8, flange1);
AudioConnection          patchCord14(envelope3, 0, mixer3, 2);
AudioConnection          patchCord15(envelope2, 0, mixer3, 1);
AudioConnection          patchCord16(envelope4, 0, mixer3, 3);
AudioConnection          patchCord17(envelope6, 0, mixer7, 1);
AudioConnection          patchCord18(envelope7, 0, mixer7, 2);
AudioConnection          patchCord19(envelope5, 0, mixer7, 0);
AudioConnection          patchCord20(envelope1, 0, mixer3, 0);
AudioConnection          patchCord21(flange1, 0, mixer7, 3);
AudioConnection          patchCord22(flange1, reverb2);
AudioConnection          patchCord23(reverb2, 0, mixer15, 2);
AudioConnection          patchCord24(reverb2, 0, mixer2, 2);
AudioConnection          patchCord25(playSdRaw7, 0, mixer15, 0);
AudioConnection          patchCord26(playSdRaw7, 1, mixer16, 0);
AudioConnection          patchCord27(playSdRaw8, 0, mixer15, 1);
AudioConnection          patchCord28(playSdRaw8, 1, mixer16, 1);
AudioConnection          patchCord29(mixer7, 0, mixer1, 1);
AudioConnection          patchCord30(mixer7, 0, mixer2, 1);
AudioConnection          patchCord31(mixer3, 0, mixer1, 0);
AudioConnection          patchCord32(mixer3, 0, mixer2, 0);
AudioConnection          patchCord33(tdm1, 0, mixer4, 1);
AudioConnection          patchCord34(tdm1, 2, mixer5, 0);
AudioConnection          patchCord35(tdm1, 4, mixer6, 0);
AudioConnection          patchCord36(tdm1, 6, mixer8, 0);
AudioConnection          patchCord37(tdm1, 8, mixer9, 0);
AudioConnection          patchCord38(tdm1, 10, mixer10, 0);
AudioConnection          patchCord39(tdm1, 12, mixer11, 0);
AudioConnection          patchCord40(tdm1, 14, mixer12, 0);
AudioConnection          patchCord41(mixer1, 0, mixer4, 0);
AudioConnection          patchCord42(mixer1, 0, mixer6, 1);
AudioConnection          patchCord43(mixer1, 0, mixer9, 1);
AudioConnection          patchCord44(mixer1, 0, mixer11, 1);
AudioConnection          patchCord45(mixer15, 0, mixer4, 2);
AudioConnection          patchCord46(mixer15, 0, mixer6, 2);
AudioConnection          patchCord47(mixer15, 0, mixer9, 2);
AudioConnection          patchCord48(mixer15, 0, mixer11, 2);
AudioConnection          patchCord49(mixer16, 0, mixer5, 2);
AudioConnection          patchCord50(mixer16, 0, mixer8, 2);
AudioConnection          patchCord51(mixer16, 0, mixer10, 2);
AudioConnection          patchCord52(mixer16, 0, mixer12, 2);
AudioConnection          patchCord53(mixer2, 0, mixer5, 1);
AudioConnection          patchCord54(mixer2, 0, mixer8, 1);
AudioConnection          patchCord55(mixer2, 0, mixer10, 1);
AudioConnection          patchCord56(mixer2, 0, mixer12, 1);
AudioConnection          patchCord57(mixer4, 0, tdm3, 0);
AudioConnection          patchCord58(mixer10, 0, tdm3, 10);
AudioConnection          patchCord59(mixer6, 0, tdm3, 4);
AudioConnection          patchCord60(mixer9, 0, tdm3, 8);
AudioConnection          patchCord61(mixer8, 0, tdm3, 6);
AudioConnection          patchCord62(mixer11, 0, tdm3, 12);
AudioConnection          patchCord63(mixer5, 0, tdm3, 2);
AudioConnection          patchCord64(mixer12, 0, tdm3, 14);
AudioControlCS42448      cs42448_1;      //xy=961.7936096191406,698.3174142837524
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

void playSample(AudioPlaySdWav &audio, String s, double rate) {
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
sequencer *guitarsequencer;

int s_idx = FLANGE_DELAY_LENGTH/4;
int s_depth = FLANGE_DELAY_LENGTH/4;
double s_freq = .5;

void setup() {
  AudioNoInterrupts();  // disable audio library momentarily
  AudioMemory(80);

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
  guitarsequencer = multisequencer.newSequencer();
  
  beatsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: 
          if (event->isNoteStartEvent) {
            envelope1.noteOn();
            triggerAudioEvent(event, playSdRaw1, "KICK.WAV");
          } else {
            envelope1.noteOff();
          }
           break;      
        default: break;
      }
  };

  snaresequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: 
          if (event->isNoteStartEvent) {
            envelope2.noteOn();
            triggerAudioEvent(event, playSdRaw2, "SNARE.WAV");
          } else {
            envelope2.noteOff();
          }
           break;      
        default: break;
      }
  };

  hatsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: 
          if (event->isNoteStartEvent) {
            envelope3.noteOn();
          } else {
            envelope3.noteOff();
          }
          triggerAudioEvent(event, playSdRaw3, "Hihat.WAV"); break;
        default: break;
      }
  };

  basssequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: 

          if (event->isNoteStartEvent) {
            sine1.frequency( event->rate * 65.41);
            envelope7.noteOn();
            envelope4.noteOn();
            triggerAudioEvent(event, playSdRaw4, "BASS.WAV"); 
          } else {
            envelope4.noteOff();
            envelope7.noteOff();
          }
          
          break;
        case 1: 
          int r = random(10); 
          if (event->isNoteStartEvent) {
            envelope5.noteOn();
          } else {
            envelope5.noteOff();
          }
          triggerAudioEvent(event, playSdRaw5, bassslidenames[r]); break;
        default: break;
      }
  };

  fxsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) { 
        case 0:
          int r = random(17); 
          if (event->isNoteStartEvent) {
            envelope6.noteOn();
          } else {
            envelope6.noteOff();
          }
          triggerAudioEvent(event, playSdRaw6, fxnames[r]); break;

        default: break;
      }
  };

  crashsequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) { 
        case 0: 
          triggerAudioEvent(event, playSdRaw7, "CRASH.WAV"); break;
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

    guitarsequencer->onevent = [] (sequencerevent *event) {

      switch(event->channel) { 
        case 0:
         if (event->isNoteStartEvent) {
           envelope8.noteOn();
           string1.noteOn(event->rate * 65.41, 0.25);
         } else {
           envelope8.noteOff();
           string1.noteOff(0.0);
         }
        break;

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
  pattern = snaresequencer->addPattern(4); // no beat 4 bars
  
  pattern++;
  adapter.loadMidi("snare.mid");
  adapter.loadMidifileToNextChannelPattern(currentChannel, 0, 8, -12);  // multicequencer channel number, midi track number, 8 bars long
  adapter.close();
  
  // hatsequencer
  currentChannel++;
  pattern = hatsequencer->addPattern(4); // no hats

  pattern++;
  adapter.loadMidi("hihat.mid");
  adapter.loadMidifileToNextChannelPattern(currentChannel, 0, 8, -12);  // multicequencer channel number, midi track number, 8 bars long
  adapter.close();
  hatsequencer->setNextPattern(pattern);

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

  pattern++;
  adapter.loadMidi("dredbass.mid");
  adapter.loadMidifileToNextChannelPattern(currentChannel, 0, 128, 12);
  adapter.close();
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

  pattern = longfxsequencer->addPattern(32); // longfx on first beat of 32 bars
  readPattern(0, pattern, xpattern4, longfxsequencer); // fx


  //guitarsequencer
  currentChannel++;
  pattern = guitarsequencer->addPattern(4); // no long fx

  pattern++;
  adapter.loadMidi("guitar.mid");
  adapter.loadMidifileToNextChannelPattern(currentChannel, 0, 128, 0);
  adapter.close();
  guitarsequencer->setNextPattern(pattern);

     
  sine1.frequency(440);
  sine1.amplitude(0.3);
  envelope1.delay(0);
  envelope2.delay(0);
  envelope3.delay(0);
  envelope4.delay(0);
  envelope5.delay(0);
  envelope6.delay(0);
  envelope7.delay(0);
  envelope8.delay(0);

  reverb1.reverbTime(0.125);
  reverb2.reverbTime(0.5);
  bitcrusher1.bits(4);

  flange1.begin(delayline,FLANGE_DELAY_LENGTH,s_idx,s_depth,s_freq);
  
  multisequencer.start(micros());
  printusage();
  
  
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
          case 1: currentSequencer = snaresequencer; break;
          case 2: currentSequencer = hatsequencer; break;
          case 3: currentSequencer = basssequencer; break;
          case 4: currentSequencer = fxsequencer; break;
          case 5: currentSequencer = crashsequencer; break;
          case 6: currentSequencer = longfxsequencer; break;
          case 7: currentSequencer = guitarsequencer; break;
          default:
            Serial.printf("invalid channel input (should be 0..6): %s\n", inputChannel);
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
    case 2: sequencer = snaresequencer; break;
    case 3: sequencer = hatsequencer; break;
    case 4: sequencer = basssequencer; break;
    case 5: sequencer = fxsequencer; break;
    case 6: sequencer = crashsequencer; break;
    case 7: sequencer = longfxsequencer; break;
    case 8: sequencer = guitarsequencer; break;
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
