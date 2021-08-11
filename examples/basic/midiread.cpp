#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <TeensyVariablePlayback.h>
#include <TeensyPolyphony.h>
#include "sequencer.h"
#include "tempo.h"
#include "midisequenceadapter.h"
#include <USBHost_t36.h>

#include <ST7735_t3.h> // Hardware-specific library
#define TFT_CS   6  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    2  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   0 // RST can use any pin
ST7735_t3 tft = ST7735_t3(TFT_CS, TFT_DC, TFT_RST);

USBHost myusb;
USBHub hub1(myusb);
MIDIDevice midi1(myusb);

tempo tempo(100.0f);
multisequencer multisequencer(tempo);
midisequenceadapter adapter(multisequencer);

#pragma region audio graph

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdRaw7;     //xy=782.1388702392578,236.66666269302368
AudioPlaySdWav           playSdRaw8;     //xy=783.6944465637207,431.25000381469727
AudioPlaySdWav           playSdRaw6;     //xy=411.50000762939453,473.25000953674316
AudioPlaySdWav           playSdRaw3;     //xy=421.00000762939453,319.5000047683716
AudioPlaySdWav           playSdRaw2;     //xy=429.25000762939453,240.50000381469727
AudioPlaySdResmp           playSdRaw4;     //xy=431.00000762939453,363.2500057220459
AudioPlaySdResmp           playSdRaw5;     //xy=432.00000762939453,423.5000057220459
AudioPlaySdWav           playSdRaw1;     //xy=435.25000762939453,169.25000095367432
AudioSynthNoiseWhite     noise1;         //xy=55,306
AudioSynthKarplusStrong  string1;        //xy=85.88887023925781,516.4088134765625
AudioFilterStateVariable filter1;        //xy=189,308
AudioSynthKarplusStrong  string6;        //xy=203,883
AudioSynthKarplusStrong  string5;        //xy=219,820
AudioMixer4              mixer19;        //xy=234,553
AudioSynthKarplusStrong  string4;        //xy=235,774
AudioSynthKarplusStrong  string3;        //xy=240.22222900390625,723
AudioSynthKarplusStrong  string2;        //xy=242.33334350585938,673.6666870117188
AudioMixer4              mixer18;        //xy=313,156
AudioMixer4              mixer13;        //xy=334,299
AudioEffectEnvelope      envelope2;      //xy=577.75,194.74999713897705
AudioMixer4              mixer17;        //xy=582,795
AudioMixer4              mixer14;        //xy=583.6666870117188,725.7777709960938
AudioEffectEnvelope      envelope3;      //xy=586.7500076293945,311.75000286102295
AudioEffectEnvelope      envelope4;      //xy=589,357
AudioEffectEnvelope      envelope6;      //xy=590.5,466.25
AudioEffectEnvelope      envelope7;      //xy=592.5,547.25
AudioEffectEnvelope      envelope1;      //xy=596.25,85.5
AudioEffectEnvelope      envelope5;      //xy=596,417
AudioEffectEnvelope      envelope8;      //xy=603.6110076904297,606.0914134979248
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
AudioConnection          patchCord1(noise1, 0, filter1, 0);
AudioConnection          patchCord2(noise1, 0, mixer18, 0);
AudioConnection          patchCord3(playSdRaw3, 0, mixer13, 0);
AudioConnection          patchCord4(string1, 0, mixer19, 0);
AudioConnection          patchCord5(playSdRaw2, 0, mixer18, 1);
AudioConnection          patchCord6(filter1, 2, mixer13, 1);
AudioConnection          patchCord13(mixer18, envelope2);
AudioConnection          patchCord14(mixer13, envelope3);
AudioConnection          patchCord15(string6, 0, mixer17, 0);
AudioConnection          patchCord16(string5, 0, mixer14, 3);
AudioConnection          patchCord17(string4, 0, mixer14, 2);
AudioConnection          patchCord18(string3, 0, mixer14, 1);
AudioConnection          patchCord19(string2, 0, mixer14, 0);
AudioConnection          patchCord20(playSdRaw6, 0, envelope6, 0);
AudioConnection          patchCord22(playSdRaw1, 0, envelope1, 0);
AudioConnection          patchCord23(playSdRaw4, 0, envelope4, 0);
AudioConnection          patchCord24(playSdRaw5, 0, envelope5, 0);
AudioConnection          patchCord25(mixer19, envelope8);
AudioConnection          patchCord26(envelope2, 0, mixer3, 1);
AudioConnection          patchCord27(mixer17, 0, mixer15, 3);
AudioConnection          patchCord28(mixer17, 0, mixer16, 2);
AudioConnection          patchCord29(mixer14, 0, mixer15, 2);
AudioConnection          patchCord30(mixer14, 0, mixer2, 2);
AudioConnection          patchCord31(envelope3, 0, mixer3, 2);
AudioConnection          patchCord32(envelope4, 0, mixer3, 3);
AudioConnection          patchCord33(envelope6, 0, mixer7, 1);
AudioConnection          patchCord35(envelope1, 0, mixer3, 0);
AudioConnection          patchCord36(envelope5, 0, mixer7, 0);
AudioConnection          patchCord39(envelope8, 0, mixer1, 3);
AudioConnection          patchCord40(playSdRaw7, 0, mixer15, 0);
AudioConnection          patchCord41(playSdRaw7, 1, mixer16, 0);
AudioConnection          patchCord42(playSdRaw8, 0, mixer15, 1);
AudioConnection          patchCord43(playSdRaw8, 1, mixer16, 1);
AudioConnection          patchCord44(mixer7, 0, mixer1, 1);
AudioConnection          patchCord45(mixer7, 0, mixer2, 1);
AudioConnection          patchCord46(mixer3, 0, mixer1, 0);
AudioConnection          patchCord47(mixer3, 0, mixer2, 0);
AudioConnection          patchCord48(tdm1, 0, mixer4, 1);
AudioConnection          patchCord49(tdm1, 2, mixer5, 0);
AudioConnection          patchCord50(tdm1, 4, mixer6, 0);
AudioConnection          patchCord51(tdm1, 6, mixer8, 0);
AudioConnection          patchCord52(tdm1, 8, mixer9, 0);
AudioConnection          patchCord53(tdm1, 10, mixer10, 0);
AudioConnection          patchCord54(mixer1, 0, mixer4, 0);
AudioConnection          patchCord55(mixer1, 0, mixer6, 1);
AudioConnection          patchCord56(mixer1, 0, mixer9, 1);
AudioConnection          patchCord57(mixer1, 0, mixer11, 1);
AudioConnection          patchCord58(mixer15, 0, mixer4, 2);
AudioConnection          patchCord59(mixer15, 0, mixer6, 2);
AudioConnection          patchCord60(mixer15, 0, mixer9, 2);
AudioConnection          patchCord61(mixer15, 0, mixer11, 2);
AudioConnection          patchCord62(mixer16, 0, mixer5, 2);
AudioConnection          patchCord63(mixer16, 0, mixer8, 2);
AudioConnection          patchCord64(mixer16, 0, mixer10, 2);
AudioConnection          patchCord65(mixer16, 0, mixer12, 2);
AudioConnection          patchCord66(mixer2, 0, mixer5, 1);
AudioConnection          patchCord67(mixer2, 0, mixer8, 1);
AudioConnection          patchCord68(mixer2, 0, mixer10, 1);
AudioConnection          patchCord69(mixer2, 0, mixer12, 1);
AudioConnection          patchCord70(mixer4, 0, tdm3, 0);
AudioConnection          patchCord71(mixer10, 0, tdm3, 10);
AudioConnection          patchCord72(mixer6, 0, tdm3, 4);
AudioConnection          patchCord73(mixer9, 0, tdm3, 8);
AudioConnection          patchCord74(mixer8, 0, tdm3, 6);
AudioConnection          patchCord75(mixer11, 0, tdm3, 12);
AudioConnection          patchCord76(mixer5, 0, tdm3, 2);
AudioConnection          patchCord77(mixer12, 0, tdm3, 14);
AudioControlCS42448      cs42448_1;      //xy=961.7936096191406,698.3174142837524
// GUItool: end automatically generated code
#pragma endregion

stringsampler guitar;
unpitchedsdwavsampler beatsampler;
unpitchedsdwavsampler snaresampler;
unpitchedsdwavsampler hatssampler;
sdwavsampler basssampler;
unpitchedsdwavsampler fxsampler;
stringsampler voicesampler;
unpitchedsdwavsampler crashsampler;
unpitchedsdwavsampler longfxsampler;

sequencer *beatsequencer;
sequencer *snaresequencer;
sequencer *hatsequencer;
sequencer *basssequencer;
sequencer *fxsequencer;
sequencer *crashsequencer;
sequencer *longfxsequencer;
sequencer *voicesequencer;
sequencer *guitarsequencer;

char *longfxnames[2] = {"LONGFX01.wav", "LONGFX02.wav"};
char *fxnames[18] = {"FX01.wav", "FX02.wav", "FX03.wav", "FX04.wav", "FX05.wav", "FX06.wav", "FX07.wav", "FX09.wav","FX10.wav", "FX21.wav", "FX28.wav","FX30.wav","FX34.wav","FX35.wav","FX40.wav","FX77.wav", "HIT1.wav", "HIT2.wav"};
char *bassslidenames[11] = {"BASSSL01.wav", "BASSSL02.wav","BASSSL03.wav","BASSSL04.wav", "BASSSL05.wav", "BASSSL06.wav","BASSSL07.wav","BASSSL08.wav","BASSSL09.wav","BASSSL10.wav","BASSSL11.wav"};

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
    //tft.println("guitar...");

    guitar.addVoice( string2 );
    guitar.addVoice( string3 );
    guitar.addVoice( string4 );
    guitar.addVoice( string5 );
    guitar.addVoice( string6 );
   
    voicesampler.addVoice( string1, envelope8 );

    beatsampler.addSample(36, "KICK.WAV");
    beatsampler.addVoice(playSdRaw1, mixer3, 0, envelope1);

    snaresampler.addSample(36, "SNARE.WAV");
    snaresampler.addVoice(playSdRaw2, mixer3, 1, envelope2);

    hatssampler.addSample(36, "HIHAT.WAV");
    hatssampler.addVoice(playSdRaw3, mixer3, 2, envelope3);

    basssampler.addSample(36, "BASS.WAV");
    basssampler.addVoice(playSdRaw4, mixer3, 3, envelope4);

    crashsampler.addSample(36, "CRASH.WAV");
    crashsampler.addVoice(playSdRaw7);

    for (unsigned i=0; i < sizeof(fxnames)/sizeof(fxnames[0]); i++ ) {
        fxsampler.addSample(36+i, fxnames[i]);
    }
    fxsampler.addVoice(playSdRaw6, mixer7, 1);

    for (unsigned i=0; i < sizeof(longfxnames)/sizeof(longfxnames[0]); i++ ) {
        longfxsampler.addSample(36+i, longfxnames[i]);
    }
    longfxsampler.addVoice(playSdRaw8);

    beatsequencer = multisequencer.newSequencer();
    snaresequencer = multisequencer.newSequencer();
    hatsequencer = multisequencer.newSequencer();
    basssequencer = multisequencer.newSequencer();
    fxsequencer = multisequencer.newSequencer();
    crashsequencer = multisequencer.newSequencer();
    longfxsequencer = multisequencer.newSequencer();
    voicesequencer = multisequencer.newSequencer();
    guitarsequencer = multisequencer.newSequencer();

    beatsequencer->onevent = [] (sequencerevent *event) {
        beatsampler.noteEvent(event->noteNumber, event->velocity, event->isNoteStartEvent, false);
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
    /*
            case 1:
                r = random(10);
                if (event->isNoteStartEvent) {
                    envelope5.noteOn();
                } else {
                    envelope5.noteOff();
                }
                triggerAudioEvent(event, playSdRaw5, bassslidenames[r], mixer7, 0); break;
            default: break;
        }
    */

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

    int pattern = 0;

    tft.println("beatsequencer...");
    // beatsequencer
    pattern = beatsequencer->addPattern(4); // no beat

    pattern++;
    adapter.loadMidi("kik.mid");
    adapter.loadMidifileToNextPattern(beatsequencer, 0, 128, 1);  // multicequencer channel number, midi track number, 8 bars long
    adapter.close();
    beatsequencer->setNextPattern(pattern);

    tft.println("snaresequencer...");
    // snaresequencer
    
    pattern = snaresequencer->addPattern(4); // no beat 4 bars

    pattern++;
    adapter.loadMidi("snare.mid");
    adapter.loadMidifileToNextPattern(snaresequencer, 0, 8, -24);  // multicequencer channel number, midi track number, 8 bars long
    adapter.close();

    tft.println("hatssequencer..");
    // hatsequencer
    
    pattern = hatsequencer->addPattern(4); // no hats

    pattern++;
    adapter.loadMidi("hihat.mid");
    adapter.loadMidifileToNextPattern(hatsequencer, 0, 8, -24);  // multicequencer channel number, midi track number, 8 bars long
    adapter.close();
    hatsequencer->setNextPattern(pattern);

    tft.println("basssequencer..");
    // basssequencer
    
    pattern = basssequencer->addPattern(4); // no bass

    pattern++;
    adapter.loadMidi("dredbass.mid");
    adapter.loadMidifileToNextPattern(basssequencer, 0, 128, 0);
    adapter.close();
    basssequencer->setNextPattern(pattern);

    tft.println("fxsequencer..");
    //fxsequencer
    
    pattern = fxsequencer->addPattern(4); // no fx

    tft.println("crashsequencer..");
    //crashsequencer
    
    pattern = crashsequencer->addPattern(8); // no crash

    //longfxsequencer
    
    pattern = longfxsequencer->addPattern(8); // no long fx

    tft.println("voicesequencer..");
    //voicesequencer
    
    pattern = voicesequencer->addPattern(4); // no long fx

    pattern++;
    adapter.loadMidi("guitar.mid");
    adapter.loadMidifileToNextPattern(voicesequencer, 0, 128, 0);
    adapter.close();
    voicesequencer->setNextPattern(pattern);

    tft.println("guitar-sequencer...t1");
    //guitar-esequencer
    
    pattern = guitarsequencer->addPattern(4); // no long fx

    pattern++;
    adapter.loadMidi("guitar2.mid");
    adapter.loadMidifileToNextPattern(guitarsequencer, 0, 128, 0);
    adapter.close();
    guitarsequencer->setNextPattern(pattern);

    tft.println("fx params...");
    envelope1.delay(0);

    envelope2.delay(0);
    envelope2.attack(0);
    envelope2.hold(0);
    envelope2.sustain(0);
    envelope2.release(7);

    //hihat
    envelope3.delay(0);
    envelope3.attack(0);
    envelope3.hold(0);
    envelope3.sustain(0);

    envelope4.delay(0);
    envelope5.delay(0);
    envelope6.delay(0);
    envelope7.delay(0);
    envelope8.delay(0);

    noise1.amplitude(0.8);
    filter1.frequency(9000);

    tft.fillScreen(ST7735_BLACK);
    tft.println("multisequencer start...");
    multisequencer.start(micros());
    printusage();
    AudioInterrupts();
    tft.println("AudioInterrupts()");
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