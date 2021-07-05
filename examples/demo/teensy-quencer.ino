#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <TeensyVariablePlayback.h>
#include <sequencer.h>
#include <songposition.h>
#include <tempo.h>
#include "looptype.h"
#include "midireader.h"
#include "midisequenceadapter.h"
#include "polyphonicsampler.h"

#include <USBHost_t36.h>

#include <ST7735_t3.h> // Hardware-specific library
#define TFT_CS   6  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    2  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   255 // RST can use any pin
ST7735_t3 tft = ST7735_t3(TFT_CS, TFT_DC, TFT_RST);

USBHost myusb;
USBHub hub1(myusb);
MIDIDevice midi1(myusb);

tempo tempo(100.0f);
multisequencer multisequencer(tempo);
midisequenceadapter adapter(multisequencer);

sequencer *guitar1sequencer;
sequencer *guitar2sequencer;
sequencer *guitar3sequencer;
sequencer *guitar4sequencer;

polyphonicsampler guitar1;
polyphonicsampler guitar2;
polyphonicsampler guitar3;
polyphonicsampler guitar4;

uint8_t polyphony = 0;
uint8_t currentSelectedTrack = 0;

#include "TFTPianoDisplay.h"
TFTPianoDisplay pianoDisplay1a(tft, 3, 3, 0, 0); //tft, byte octaves, byte startOctave, byte x, byte y
TFTPianoDisplay pianoDisplay1b(tft, 3, 6, 0, 16); //tft, byte octaves, byte startOctave, byte x, byte y

TFTPianoDisplay pianoDisplay2a(tft, 3, 3, 0, 32); //tft, byte octaves, byte startOctave, byte x, byte y
TFTPianoDisplay pianoDisplay2b(tft, 3, 6, 0, 48); //tft, byte octaves, byte startOctave, byte x, byte y

TFTPianoDisplay pianoDisplay3a(tft, 3, 3, 0, 64); //tft, byte octaves, byte startOctave, byte x, byte y
TFTPianoDisplay pianoDisplay3b(tft, 3, 6, 0, 80); //tft, byte octaves, byte startOctave, byte x, byte y

TFTPianoDisplay pianoDisplay4a(tft, 3, 3, 0, 94); //tft, byte octaves, byte startOctave, byte x, byte y
TFTPianoDisplay pianoDisplay4b(tft, 3, 6, 0, 110); //tft, byte octaves, byte startOctave, byte x, byte y

// GUItool: begin automatically generated code
AudioSynthKarplusStrong  string4f;       //xy=210,575
AudioSynthKarplusStrong  string1b;        //xy=213,87
AudioSynthKarplusStrong  string4c;        //xy=212,466
AudioSynthKarplusStrong  string4g;       //xy=212,612
AudioSynthKarplusStrong  string4b;        //xy=213,430
AudioSynthKarplusStrong  string4d;       //xy=213,501
AudioSynthKarplusStrong  string4e;       //xy=213,538
AudioSynthKarplusStrong  string1a;        //xy=216,46
AudioSynthKarplusStrong  string4a;        //xy=215,390
AudioSynthKarplusStrong  string3a;        //xy=232,267
AudioSynthKarplusStrong  string3b;        //xy=236,302
AudioSynthKarplusStrong  string2a;        //xy=251,154
AudioSynthKarplusStrong  string2b;        //xy=252,188
AudioEffectEnvelope      envelope4g;     //xy=382,619
AudioEffectEnvelope      envelope4f;      //xy=383,580
AudioEffectEnvelope      envelope4d;      //xy=386,504
AudioEffectEnvelope      envelope4a;      //xy=387,375
AudioEffectEnvelope      envelope4e;      //xy=387,543
AudioEffectEnvelope      envelope4b;      //xy=388,423
AudioEffectEnvelope      envelope4c;      //xy=389,467
AudioEffectEnvelope      envelope3b;     //xy=411,304
AudioEffectEnvelope      envelope3a;      //xy=412.75,265.75
AudioEffectEnvelope      envelope2a;      //xy=429.75,149.75
AudioEffectEnvelope      envelope2b;     //xy=430,187
AudioEffectEnvelope      envelope1a;      //xy=444.25,55.5
AudioEffectEnvelope      envelope1b;     //xy=446,93
AudioMixer4              mixer3;         //xy=565,298
AudioMixer4              mixer4b;         //xy=596,559
AudioMixer4              mixer2;         //xy=602,176
AudioMixer4              mixer1;         //xy=603,77
AudioMixer4              mixer4a;         //xy=616,414
AudioMixer4              mixer10;         //xy=783.75,191.5
AudioMixer4              mixerL;         //xy=958.75,194.5
AudioMixer4              mixerR;         //xy=960.75,376.5
AudioOutputTDM           tdmOUT;           //xy=1156.75,292.5
AudioConnection          patchCord1(string4f, envelope4f);
AudioConnection          patchCord2(string1b, envelope1b);
AudioConnection          patchCord3(string4c, envelope4c);
AudioConnection          patchCord4(string4g, envelope4g);
AudioConnection          patchCord5(string4b, envelope4b);
AudioConnection          patchCord6(string4d, envelope4d);
AudioConnection          patchCord7(string4e, envelope4e);
AudioConnection          patchCord8(string1a, envelope1a);
AudioConnection          patchCord9(string4a, envelope4a);
AudioConnection          patchCord10(string3a, envelope3a);
AudioConnection          patchCord11(string3b, envelope3b);
AudioConnection          patchCord12(string2a, envelope2a);
AudioConnection          patchCord13(string2b, envelope2b);
AudioConnection          patchCord14(envelope4g, 0, mixer4b, 2);
AudioConnection          patchCord15(envelope4f, 0, mixer4b, 1);
AudioConnection          patchCord16(envelope4d, 0, mixer4a, 3);
AudioConnection          patchCord17(envelope4a, 0, mixer4a, 0);
AudioConnection          patchCord18(envelope4e, 0, mixer4b, 0);
AudioConnection          patchCord19(envelope4b, 0, mixer4a, 1);
AudioConnection          patchCord20(envelope4c, 0, mixer4a, 2);
AudioConnection          patchCord21(envelope3b, 0, mixer3, 1);
AudioConnection          patchCord22(envelope3a, 0, mixer3, 0);
AudioConnection          patchCord23(envelope2a, 0, mixer2, 0);
AudioConnection          patchCord24(envelope2b, 0, mixer2, 1);
AudioConnection          patchCord25(envelope1a, 0, mixer1, 0);
AudioConnection          patchCord26(envelope1b, 0, mixer1, 1);
AudioConnection          patchCord27(mixer3, 0, mixer10, 2);
AudioConnection          patchCord28(mixer4b, 0, mixerL, 2);
AudioConnection          patchCord29(mixer4b, 0, mixerR, 2);
AudioConnection          patchCord30(mixer2, 0, mixer10, 1);
AudioConnection          patchCord31(mixer1, 0, mixer10, 0);
AudioConnection          patchCord32(mixer4a, 0, mixerL, 1);
AudioConnection          patchCord33(mixer4a, 0, mixerR, 1);
AudioConnection          patchCord34(mixer10, 0, mixerL, 0);
AudioConnection          patchCord35(mixer10, 0, mixerR, 0);
AudioConnection          patchCord36(mixerL, 0, tdmOUT, 0);
AudioConnection          patchCord37(mixerL, 0, tdmOUT, 4);
AudioConnection          patchCord38(mixerL, 0, tdmOUT, 8);
AudioConnection          patchCord39(mixerL, 0, tdmOUT, 12);
AudioConnection          patchCord40(mixerR, 0, tdmOUT, 2);
AudioConnection          patchCord41(mixerR, 0, tdmOUT, 6);
AudioConnection          patchCord42(mixerR, 0, tdmOUT, 10);
AudioConnection          patchCord43(mixerR, 0, tdmOUT, 14);
AudioControlCS42448      cs42448_1;      //xy=851.7935791015625,607.3174438476562
// GUItool: end automatically generated code

void myNoteOn(byte channel, byte note, byte velocity);
void myControlChange(byte channel, byte control, byte value);
void myNoteOff(byte channel, byte note, byte velocity);

double calcFrequency(uint8_t note) {
    double result = 440.0 * pow(2.0, (note-69) / 12.0);
    return result;
}

void guitar_note(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger, AudioSynthKarplusStrong &stringVoice, AudioEffectEnvelope &envelope){
    if (isNoteOn) {
      if (!isretrigger) polyphony++;
      
      double f = calcFrequency(noteNumber);
      envelope.noteOn();
      stringVoice.noteOn(f, velocity/128.0);
    } else {
      stringVoice.noteOff(0);
      envelope.noteOff();
      polyphony--;
    }
    //Serial.printf("poly: %d\n", polyphony);
}

void guitar1_note1(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string1a, envelope1a); }
void guitar1_note2(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string1b, envelope1b); }

void guitar2_note1(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string2a, envelope2a); }
void guitar2_note2(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string2b, envelope1b); }

void guitar3_note1(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string3a, envelope3a); }
void guitar3_note2(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string3a, envelope3b); }

void guitar4_note1(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string4a, envelope4a); }
void guitar4_note2(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string4b, envelope4b); }
void guitar4_note3(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string4c, envelope4c); }
void guitar4_note4(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string4d, envelope4d); }
void guitar4_note5(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string4e, envelope4e); }
void guitar4_note6(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string4f, envelope4f); }
void guitar4_note7(uint8_t noteNumber, uint8_t velocity, bool isNoteOn, bool isretrigger) {  guitar_note(noteNumber, velocity, isNoteOn, isretrigger, string4g, envelope4g); }


void sequenceGuitarEvent( sequencerevent *event, polyphonicsampler &sampler, TFTPianoDisplay &tftPianoDisplay1, TFTPianoDisplay &tftPianoDisplay2) {
  if (event->isNoteStartEvent) {
    sampler.noteOn(event->noteNumber, event->velocity);
    tftPianoDisplay1.keyDown(event->noteNumber);
    tftPianoDisplay2.keyDown(event->noteNumber);
  } else if (event->status == 0x80) {
    sampler.noteOff(event->noteNumber);
    tftPianoDisplay1.keyUp(event->noteNumber);
    tftPianoDisplay2.keyUp(event->noteNumber);
  }
};

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

  tft.println("sd..."); 
  myusb.begin();
  tft.println("usb..."); 

  midi1.setHandleNoteOn(myNoteOn);
  midi1.setHandleNoteOff(myNoteOff);
  midi1.setHandleControlChange(myControlChange);
  tft.println("midi1"); 

  // put your setup code here, to run once:
  //cs42448_1.setAddress(0);
  cs42448_1.enable();
  cs42448_1.volume(1);
  //cs42448_1.inputLevel(1);
  tft.println("cs42448"); 

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

  tft.fillScreen(ST7735_BLACK);
  
  guitar1.pushNoteFunction( guitar1_note1 );
  guitar1.pushNoteFunction( guitar1_note2 );
  
  guitar2.pushNoteFunction( guitar2_note1 );
  guitar2.pushNoteFunction( guitar2_note2 );

  guitar3.pushNoteFunction( guitar3_note1 );
  guitar3.pushNoteFunction( guitar3_note2 );

  guitar4.pushNoteFunction( guitar4_note1 );
  guitar4.pushNoteFunction( guitar4_note2 );
  guitar4.pushNoteFunction( guitar4_note3 );
  guitar4.pushNoteFunction( guitar4_note4 );
  guitar4.pushNoteFunction( guitar4_note5 );
  guitar4.pushNoteFunction( guitar4_note6 );
  guitar4.pushNoteFunction( guitar4_note7 );

  tft.println("sequencer..."); 
  
  guitar1sequencer = multisequencer.newSequencer();
  guitar2sequencer = multisequencer.newSequencer();
  guitar3sequencer = multisequencer.newSequencer();
  guitar4sequencer = multisequencer.newSequencer();
  
  guitar1sequencer->onevent = [] (sequencerevent *event) { sequenceGuitarEvent(event, guitar1, pianoDisplay1a, pianoDisplay1b);  };
  guitar2sequencer->onevent = [] (sequencerevent *event) { sequenceGuitarEvent(event, guitar2, pianoDisplay2a, pianoDisplay2b);  };
  guitar3sequencer->onevent = [] (sequencerevent *event) { sequenceGuitarEvent(event, guitar3, pianoDisplay3a, pianoDisplay3b);  };
  guitar4sequencer->onevent = [] (sequencerevent *event) { sequenceGuitarEvent(event, guitar4, pianoDisplay4a, pianoDisplay4b);  };

  guitar1sequencer->onloopend = [] (sequencer *sequencer, int pattern) { guitar1.turnOffAllNotesStillPlaying(); };
  guitar2sequencer->onloopend = [] (sequencer *sequencer, int pattern) { guitar2.turnOffAllNotesStillPlaying(); };
  guitar3sequencer->onloopend = [] (sequencer *sequencer, int pattern) { guitar3.turnOffAllNotesStillPlaying(); };
  guitar4sequencer->onloopend = [] (sequencer *sequencer, int pattern) { guitar4.turnOffAllNotesStillPlaying(); };

  int pattern = 0;
  int currentChannel = 0;

  sequencer *tempoSequencer = multisequencer.getTempoSequencer();
  
  adapter.loadMidi("innuendo.mid");
  adapter.loadMidiTempoTrack(0, 42, 4); // track 0, 42 * 4 beats, offset by 4 bars
  
  // guitar 1 sequencer
  pattern = guitar1sequencer->addPattern(4); // no beat

  pattern++;
  adapter.loadMidi("innuendo.mid");
  adapter.loadMidifileToNextChannelPattern(currentChannel, 1, 42, 0);  // multicequencer channel number, midi track number, 35 bars long
  guitar1sequencer->setNextPattern(pattern);
  
  // guitar 2 sequencer
  currentChannel++;
  pattern = guitar2sequencer->addPattern(4); // no beat 4 bars
  
  pattern++;
  adapter.loadMidifileToNextChannelPattern(currentChannel, 2, 42, 0);  // multicequencer channel number, midi track number, 35 bars long
  guitar2sequencer->setNextPattern(pattern);
  
  // guitar 3 sequencer
  currentChannel++;
  pattern = guitar3sequencer->addPattern(4); // no hats

  pattern++;
  adapter.loadMidifileToNextChannelPattern(currentChannel, 3, 42, 0);  // multicequencer channel number, midi track number, 35 bars long
  guitar3sequencer->setNextPattern(pattern);

  // guitar 4 sequencer
  currentChannel++;
  pattern = guitar4sequencer->addPattern(4); // no bass

  pattern++;
  adapter.loadMidifileToNextChannelPattern(currentChannel, 4, 42, 0);
  adapter.close();
  guitar4sequencer->setNextPattern(pattern);

  envelope1a.delay(0);
  envelope1b.delay(0);
 
  envelope2a.delay(0);
  envelope2b.delay(0);

  envelope3a.delay(0);
  envelope3b.delay(0);

  envelope4a.delay(0);
  envelope4b.delay(0);
  envelope4c.delay(0);
  envelope4d.delay(0);
  envelope4e.delay(0);
  envelope4f.delay(0);
  envelope4g.delay(0);

  mixer4a.gain(0, 1.0 / 2.0);
  mixer4a.gain(1, 1.0 / 2.0);
  mixer4a.gain(2, 1.0 / 2.0);
  mixer4a.gain(3, 1.0 / 2.0);

  mixer4b.gain(0, 1.0 / 2.0);
  mixer4b.gain(1, 1.0 / 2.0);
  mixer4b.gain(2, 1.0 / 2.0);

  tft.fillScreen(ST7735_BLACK);
  multisequencer.start(micros());
  AudioInterrupts();     
}

String inputChannel="", inString = ""; 
bool inputChannelEntered = false;
float oldBPM = 0.0;
float newBPM = 0.0;
long bpmIndicatorTimer = 0;
 
void loop() {
  myusb.Task();
  midi1.read();

  if (pianoDisplay1a.displayNeedsUpdating())
    pianoDisplay1a.drawPiano();
  if (pianoDisplay1b.displayNeedsUpdating())
    pianoDisplay1b.drawPiano();
    
  if (pianoDisplay2a.displayNeedsUpdating())
    pianoDisplay2a.drawPiano();
  if (pianoDisplay2b.displayNeedsUpdating())
    pianoDisplay2b.drawPiano();
    
  if (pianoDisplay3a.displayNeedsUpdating())
    pianoDisplay3a.drawPiano();
  if (pianoDisplay3b.displayNeedsUpdating())
    pianoDisplay3b.drawPiano();
    
  if (pianoDisplay4a.displayNeedsUpdating())
    pianoDisplay4a.drawPiano();
  if (pianoDisplay4b.displayNeedsUpdating())
    pianoDisplay4b.drawPiano();
    
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
    case 1: sequencer = guitar1sequencer; break;
    case 2: sequencer = guitar2sequencer; break;
    case 3: sequencer = guitar3sequencer; break;
    case 4: sequencer = guitar4sequencer; break;
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
  } else if (( 16 <= control) && ( control <= 23)) {
    if (currentSelectedTrack != channel - 1) {
      currentSelectedTrack = channel - 1;
      Serial.printf("Current selected track: %d\n", currentSelectedTrack);
    }
    
    AudioEffectEnvelope *envelope = NULL;
    switch (currentSelectedTrack) {
      case 0: envelope = &envelope1a; break;
      case 1: envelope = &envelope1b; break;
      case 2: envelope = &envelope2a; break;
      case 3: envelope = &envelope2b; break;
      case 4: envelope = &envelope3a; break;
      case 5: envelope = &envelope3b; break;
      case 6: envelope = &envelope4a; break;
      case 7: envelope = &envelope4b; break;
      default:
        break;  
    }

    if (envelope != NULL) {
      Serial.printf("control: %d\n - value: %d", control, value);
      switch (control) {
        case 16: envelope->delay(value ); break;
        case 17: envelope->attack(value); break;
        case 18: envelope->hold(value); break;
        case 19: envelope->sustain(value); break;
        case 20: envelope->release(value); break;
        case 21: envelope->releaseNoteOn(value); break;
        case 22: break;
        case 23: break;
        default:
          break;  
      } 
    }      
  }
  else if (control == 7) {
    // volume slider
  }
}

void akaiLED(byte channel, byte pattern, bool on) {
  midi1.sendNoteOn(53+pattern, (on)? 127 : 0, channel);
}

unsigned __exidx_start;
unsigned __exidx_end;
