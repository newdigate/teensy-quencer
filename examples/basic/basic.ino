#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <TeensyVariablePlayback.h>
#include <TeensyPolyphony.h>
#include <Teensyquencer.h>
#include <USBHost_t36.h>
#include <ST7735_t3.h> // Hardware-specific library
#define TFT_CS   6  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    2  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   0 // RST can use any pin
ST7735_t3 tft = ST7735_t3(TFT_CS, TFT_DC, TFT_RST);

USBHost myusb;
USBHub hub1(myusb);
MIDIDevice midi1(myusb);
using namespace newdigate;

tempo songtempo(100.0f);
multisequencer multiseq(songtempo);
midisequenceadapter adapter(multiseq);

#pragma region audio graph

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWavKick;  //xy=854,334
AudioPlaySdWav           playSdWavSnare; //xy=870,389
AudioPlaySdResmp         playSdResmpBass; //xy=896,522
AudioPlaySdWav           playSdHats;     //xy=910,460
AudioPlaySdWav           playSdWavFx;    //xy=916,636
AudioPlaySdResmp         playSdRaw5;     //xy=937,586
AudioSynthKarplusStrong  stringVoice;    //xy=986,877
AudioEffectEnvelope      envelopeSnare;  //xy=1066,383
AudioEffectEnvelope      envelopeKick;   //xy=1069,328
AudioEffectEnvelope      envelopeHats;   //xy=1085,452
AudioEffectEnvelope      envelopeBass;   //xy=1094,520
AudioEffectEnvelope      envelopeFx;     //xy=1095,629
AudioEffectEnvelope      envelope5;      //xy=1101,580
AudioSynthKarplusStrong  string6;        //xy=1104,1244
AudioSynthKarplusStrong  string5;        //xy=1120,1181
AudioSynthKarplusStrong  string4;        //xy=1136,1135
AudioSynthKarplusStrong  string3;        //xy=1141,1084
AudioSynthKarplusStrong  string2;        //xy=1143,1034
AudioEffectEnvelope      envelope8;      //xy=1352,875
AudioPlaySdWav           playSdWavLongFx; //xy=1364,780
AudioPlaySdWav           playSdCrash;    //xy=1371,699
AudioMixer4              mixer3;         //xy=1468,405
AudioMixer4              mixer7;         //xy=1468,478
AudioMixer4              mixer17;        //xy=1483,1156
AudioMixer4              mixer14;        //xy=1484,1086
AudioMixer4              mixer1;         //xy=1863,600
AudioMixer4              mixer15;        //xy=1864,536
AudioMixer4              mixer16;        //xy=1865,983
AudioMixer4              mixer2;         //xy=1866,917
AudioMixer4              mixerLeft1;     //xy=2075,483
AudioMixer4              mixerLeft2;     //xy=2075,544
AudioMixer4              mixerLeft3;     //xy=2075,605
AudioMixer4              mixerLeft4;     //xy=2075,666
AudioMixer4              mixerRight1;    //xy=2075,805
AudioMixer4              mixerRight2;    //xy=2075,869
AudioMixer4              mixerRight3;    //xy=2075,934
AudioMixer4              mixerRight4;    //xy=2075,998
AudioOutputTDM           tdmout;         //xy=2280,781
AudioConnection          patchCord1(playSdWavKick, 0, envelopeKick, 0);
AudioConnection          patchCord2(playSdWavSnare, 0, envelopeSnare, 0);
AudioConnection          patchCord3(playSdResmpBass, 0, envelopeBass, 0);
AudioConnection          patchCord4(playSdHats, 0, envelopeHats, 0);
AudioConnection          patchCord5(playSdWavFx, 0, envelopeFx, 0);
AudioConnection          patchCord6(playSdRaw5, 0, envelope5, 0);
AudioConnection          patchCord7(stringVoice, envelope8);
AudioConnection          patchCord8(envelopeSnare, 0, mixer3, 1);
AudioConnection          patchCord9(envelopeKick, 0, mixer3, 0);
AudioConnection          patchCord10(envelopeHats, 0, mixer3, 2);
AudioConnection          patchCord11(envelopeBass, 0, mixer3, 3);
AudioConnection          patchCord12(envelopeFx, 0, mixer7, 1);
AudioConnection          patchCord13(envelope5, 0, mixer7, 0);
AudioConnection          patchCord14(string6, 0, mixer17, 0);
AudioConnection          patchCord15(string5, 0, mixer14, 3);
AudioConnection          patchCord16(string4, 0, mixer14, 2);
AudioConnection          patchCord17(string3, 0, mixer14, 1);
AudioConnection          patchCord18(string2, 0, mixer14, 0);
AudioConnection          patchCord19(envelope8, 0, mixer1, 3);
AudioConnection          patchCord20(envelope8, 0, mixer16, 3);
AudioConnection          patchCord21(playSdWavLongFx, 0, mixer15, 1);
AudioConnection          patchCord22(playSdWavLongFx, 1, mixer16, 1);
AudioConnection          patchCord23(playSdCrash, 0, mixer15, 0);
AudioConnection          patchCord24(playSdCrash, 1, mixer16, 0);
AudioConnection          patchCord25(mixer3, 0, mixer1, 0);
AudioConnection          patchCord26(mixer3, 0, mixer2, 0);
AudioConnection          patchCord27(mixer7, 0, mixer1, 1);
AudioConnection          patchCord28(mixer7, 0, mixer2, 1);
AudioConnection          patchCord29(mixer17, 0, mixer15, 3);
AudioConnection          patchCord30(mixer17, 0, mixer16, 2);
AudioConnection          patchCord31(mixer14, 0, mixer15, 2);
AudioConnection          patchCord32(mixer14, 0, mixer2, 2);
AudioConnection          patchCord33(mixer1, 0, mixerLeft1, 0);
AudioConnection          patchCord34(mixer1, 0, mixerLeft2, 1);
AudioConnection          patchCord35(mixer1, 0, mixerLeft3, 1);
AudioConnection          patchCord36(mixer1, 0, mixerLeft4, 1);
AudioConnection          patchCord37(mixer15, 0, mixerLeft1, 2);
AudioConnection          patchCord38(mixer15, 0, mixerLeft2, 2);
AudioConnection          patchCord39(mixer15, 0, mixerLeft3, 2);
AudioConnection          patchCord40(mixer15, 0, mixerLeft4, 2);
AudioConnection          patchCord41(mixer16, 0, mixerRight1, 2);
AudioConnection          patchCord42(mixer16, 0, mixerRight2, 2);
AudioConnection          patchCord43(mixer16, 0, mixerRight3, 2);
AudioConnection          patchCord44(mixer16, 0, mixerRight4, 2);
AudioConnection          patchCord45(mixer2, 0, mixerRight1, 1);
AudioConnection          patchCord46(mixer2, 0, mixerRight2, 1);
AudioConnection          patchCord47(mixer2, 0, mixerRight3, 1);
AudioConnection          patchCord48(mixer2, 0, mixerRight4, 1);
AudioConnection          patchCord49(mixerLeft1, 0, tdmout, 0);
AudioConnection          patchCord50(mixerLeft2, 0, tdmout, 4);
AudioConnection          patchCord51(mixerLeft3, 0, tdmout, 8);
AudioConnection          patchCord52(mixerLeft4, 0, tdmout, 12);
AudioConnection          patchCord53(mixerRight1, 0, tdmout, 2);
AudioConnection          patchCord54(mixerRight2, 0, tdmout, 6);
AudioConnection          patchCord55(mixerRight3, 0, tdmout, 10);
AudioConnection          patchCord56(mixerRight4, 0, tdmout, 14);
AudioControlCS42448      cs42448;        //xy=1862,1059
// GUItool: end automatically generated code

#pragma endregion

stringsampler guitar;
unpitchedsdwavsampler kicksampler;
unpitchedsdwavsampler snaresampler;
unpitchedsdwavsampler hatssampler;
sdwavsampler basssampler;
unpitchedsdwavsampler fxsampler;
stringsampler voicesampler;
unpitchedsdwavsampler crashsampler;
unpitchedsdwavsampler longfxsampler;

sequencer *kicksequencer;
sequencer *snaresequencer;
sequencer *hatsequencer;
sequencer *basssequencer;
sequencer *fxsequencer;
sequencer *crashsequencer;
sequencer *longfxsequencer;
sequencer *voicesequencer;
sequencer *guitarsequencer;

const char *longfxnames[2] = {"LONGFX01.wav", "LONGFX02.wav"};
const char *fxnames[18] = {"FX01.wav", "FX02.wav", "FX03.wav", "FX04.wav", "FX05.wav", "FX06.wav", "FX07.wav", "FX09.wav","FX10.wav", "FX21.wav", "FX28.wav","FX30.wav","FX34.wav","FX35.wav","FX40.wav","FX77.wav", "HIT1.wav", "HIT2.wav"};

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
        case 1: sequencer = kicksequencer; break;
        case 2: sequencer = snaresequencer; break;
        case 3: sequencer = hatsequencer; break;
        case 4: sequencer = basssequencer; break;
        case 5: sequencer = fxsequencer; break;
        case 6: sequencer = crashsequencer; break;
        case 7: sequencer = longfxsequencer; break;
        case 8: sequencer = voicesequencer; break;
        case 9: sequencer = guitarsequencer; break;
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
        double newBPM = 100.0f + value/2.0f;
        Serial.printf("BPM: %f\n",newBPM);

        songtempo.setBeatsPerMinute(newBPM);

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

void setup() {
    AudioNoInterrupts();  // disable audio library momentarily
    AudioMemory(100);

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
    //cs42448.setAddress(0);
    cs42448.enable();
    cs42448.volume(1);
    //cs42448.inputLevel(1);
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

    // turn off all leds on the akai APC40
    for (int j=0; j<8;j++)
        for (int i=0; i<5;i++)
            midi1.sendNoteOff(53+i, 0, j+1);

    multiseq.onloopchange = [&] (long channel, long pattern) {
        Serial.printf("channel %d, pattern changed to %d\n", channel, pattern);
        for (int i=0; i<5;i++)
            midi1.sendNoteOff(53+i, 0, channel+1);

        midi1.sendNoteOn(53 + pattern, 1, channel+1);  // green
    };

    tft.fillScreen(ST7735_BLACK);

    voicesampler.addVoice( stringVoice, envelope8 );

    guitar.addVoice( string2 );
    guitar.addVoice( string3 );
    guitar.addVoice( string4 );
    guitar.addVoice( string5 );
    guitar.addVoice( string6 );   

    kicksampler.addSample(36, "KICK.WAV");
    kicksampler.addVoice(playSdWavKick, mixer3, 0, envelopeKick);

    snaresampler.addSample(36, "SNARE.WAV");
    snaresampler.addVoice(playSdWavSnare, mixer3, 1, envelopeSnare);

    hatssampler.addSample(36, "HIHAT.WAV");
    hatssampler.addVoice(playSdHats, mixer3, 2, envelopeHats);

    basssampler.addSample(36, "BASS.WAV");
    basssampler.addVoice(playSdResmpBass, mixer3, 3, envelopeBass);

    crashsampler.addSample(36, "CRASH.WAV");
    crashsampler.addVoice(playSdCrash);

    for (unsigned i=0; i < sizeof(fxnames)/sizeof(fxnames[0]); i++ ) {
        fxsampler.addSample(36+i, fxnames[i]);
    }
    fxsampler.addVoice(playSdWavFx, mixer7, 1);

    for (unsigned i=0; i < sizeof(longfxnames)/sizeof(longfxnames[0]); i++ ) {
        longfxsampler.addSample(36+i, longfxnames[i]);
    }
    longfxsampler.addVoice(playSdWavLongFx);

    kicksequencer = multiseq.newSequencer();
    snaresequencer = multiseq.newSequencer();
    hatsequencer = multiseq.newSequencer();
    basssequencer = multiseq.newSequencer();
    fxsequencer = multiseq.newSequencer();
    crashsequencer = multiseq.newSequencer();
    longfxsequencer = multiseq.newSequencer();
    voicesequencer = multiseq.newSequencer();
    guitarsequencer = multiseq.newSequencer();

    kicksequencer->onevent = [] (sequencerevent *event) {
        kicksampler.noteEvent(event->noteNumber, event->velocity, event->isNoteStartEvent, false);
    };

    snaresequencer->onevent = [] (sequencerevent *event) {
        snaresampler.noteEvent(event->noteNumber, event->velocity, event->isNoteStartEvent, false);
    };

    hatsequencer->onevent = [] (sequencerevent *event) {
        hatssampler.noteEvent(event->noteNumber, event->velocity, event->isNoteStartEvent, false);
    };

    basssequencer->onevent = [] (sequencerevent *event) {
        basssampler.noteEvent(event->noteNumber, event->velocity, event->isNoteStartEvent, false);
    };

    fxsequencer->onevent = [] (sequencerevent *event) {
        fxsampler.noteEvent(event->noteNumber, event->velocity, event->isNoteStartEvent, false);
    };

    crashsequencer->onevent = [] (sequencerevent *event) {
        crashsampler.noteEvent(event->noteNumber, event->velocity, event->isNoteStartEvent, false);
    };

    longfxsequencer->onevent = [] (sequencerevent *event) {
        longfxsampler.noteEvent(event->noteNumber, event->velocity, event->isNoteStartEvent, false);
    };

    voicesequencer->onevent = [] (sequencerevent *event) {
        voicesampler.noteEvent(event->noteNumber, event->velocity, event->isNoteStartEvent, false);
    };

    guitarsequencer->onevent = [] (sequencerevent *event) {
        guitar.noteEvent(event->noteNumber, event->velocity / 2.0, event->isNoteStartEvent, false);
    };

    pattern *pattern = nullptr;

    // kicksequencer
    pattern = kicksequencer->addPattern(4); // no beat
    pattern = adapter.loadMidifileToNextPattern("kik.mid", kicksequencer, 0, 128, 1);  // multicequencer channel number, midi track number, 8 bars long
    kicksequencer->setNextPattern(pattern);

    //                        !               !               !               !      
    const char* pattern4x4 = "X...X...X...X...X...X...X...X...X...X...X...X...X...X...X...X..."; 
    pattern = kicksequencer->readPattern(pattern4x4, 0, 54); // kick 4x4, channel 0, note 54

    // snaresequencer
    pattern = snaresequencer->addPattern(4); // no beat 4 bars
    pattern = adapter.loadMidifileToNextPattern("snare.mid", snaresequencer, 0, 8, -24);  // multicequencer channel number, midi track number, 8 bars long
    snaresequencer->setNextPattern(pattern);

    //                        !               !               !               !      
    const char* patternSnr = "....x.......x.......x.......x.......x.......x.......x.......x..."; 
    pattern = snaresequencer->readPattern(patternSnr, 0, 54); // kick 4x4, channel 0, note 54

    // hatsequencer
    pattern = hatsequencer->addPattern(4); // no hats
    pattern = adapter.loadMidifileToNextPattern("hihat.mid", hatsequencer, 0, 8, -24);  // multicequencer channel number, midi track number, 8 bars long
    hatsequencer->setNextPattern(pattern);

    // basssequencer
    pattern = basssequencer->addPattern(4); // no bass
    pattern = adapter.loadMidifileToNextPattern("dredbass.mid", basssequencer, 0, 128, 0);
    basssequencer->setNextPattern(pattern);

    // fxsequencer
    pattern = fxsequencer->addPattern(4); // no fx

    //crashsequencer
    pattern = crashsequencer->addPattern(8); // no crash

    //longfxsequencer
    pattern = longfxsequencer->addPattern(8); // no long fx

    //voicesequencer
    pattern = voicesequencer->addPattern(4); // no long fx
    pattern = adapter.loadMidifileToNextPattern("guitar.mid", voicesequencer, 0, 128, 0);
    voicesequencer->setNextPattern(pattern);

    //guitar-sequencer
    pattern = guitarsequencer->addPattern(4); // no long fx
    pattern = adapter.loadMidifileToNextPattern("guitar2.mid", guitarsequencer, 0, 128, 0);
    guitarsequencer->setNextPattern(pattern);

    envelopeKick.delay(0);
    envelopeSnare.delay(0);
    envelopeSnare.attack(0);
    envelopeSnare.hold(0);
    envelopeSnare.sustain(0);
    envelopeSnare.release(7);

    //hihat
    envelopeHats.delay(0);
    envelopeHats.attack(0);
    envelopeHats.hold(0);
    envelopeHats.sustain(0);

    envelopeBass.delay(0);
    envelope5.delay(0);
    envelopeFx.delay(0);
    envelope8.delay(0);

    tft.fillScreen(ST7735_BLACK);
    tft.println("multisequencer start...");
    multiseq.start(micros());
    printusage();
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
    multiseq.tick(micros());


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
                    case 0: currentSequencer = kicksequencer; break;
                    case 1: currentSequencer = snaresequencer; break;
                    case 2: currentSequencer = hatsequencer; break;
                    case 3: currentSequencer = basssequencer; break;
                    case 4: currentSequencer = fxsequencer; break;
                    case 5: currentSequencer = crashsequencer; break;
                    case 6: currentSequencer = longfxsequencer; break;
                    case 7: currentSequencer = voicesequencer; break;
                    case 8: currentSequencer = guitarsequencer; break;
                    default:
                        Serial.printf("invalid channel input (should be 0..8): %s\n", inputChannel.c_str());
                        break;
                }

                if (currentSequencer != NULL) {
                    Serial.printf("setting next patteren to %d\n", inString.toInt());
                    currentSequencer->setNextPattern(inString.toInt());
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

unsigned __exidx_start;
unsigned __exidx_end;