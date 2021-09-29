#include <Audio.h>
#include <SD.h>
#include <Teensyquencer.h>

using namespace newdigate;

tempo songtempo(100.0f);
multisequencer multiseq(songtempo);
midisequenceadapter adapter(multiseq);

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWavKick;  //xy=994.2857055664062,490
AudioPlaySdWav           playSdWavSnare; //xy=1010.2857055664062,545
AudioOutputI2S           i2s1;           //xy=1554.2857142857142,518.5714285714286
AudioConnection          patchCord1(playSdWavKick, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWavSnare, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000;     //xy=1235.7142791748047,641.4285697937012
// GUItool: end automatically generated code

sequencer *kicksequencer;
sequencer *snaresequencer;

void setup() {
    AudioNoInterrupts();  // disable audio library momentarily
    AudioMemory(100);

    Serial.begin(9600);

    while (!(SD.begin(BUILTIN_SDCARD))) {
        // stop here if no SD card, but print a message
        Serial.println("Unable to access the SD card");
        delay(1000);
    }

    sgtl5000.enable();
    sgtl5000.volume(1);

    multiseq.onloopchange = [&] (long channel, long pattern) {
        Serial.printf("channel %d, pattern changed to %d\n", channel, pattern);
    };

    kicksequencer = multiseq.newSequencer();
    snaresequencer = multiseq.newSequencer();

    kicksequencer->onevent = [] (sequencerevent *event) {
        playSdWavKick.play("KICK.WAV");
    };

    snaresequencer->onevent = [] (sequencerevent *event) {
        playSdWavKick.play("SNARE.WAV");
    };

    pattern *pattern = nullptr;

    // kicksequencer
    //                        !               !               !               !      
    const char* pattern4x4 = "X...X...X...X...X...X...X...X...X...X...X...X...X...X...X...X..."; 
    const char* pattern8x4 = "X.......X.......X.......X.......X.......X.......X.......X......."; 
    pattern = kicksequencer->readPattern(pattern4x4, 0, 54); // kick 4x4, channel 0, note 54
    kicksequencer->setNextPattern(pattern);
    pattern = kicksequencer->readPattern(pattern8x4, 0, 54); // kick 8x4, channel 0, note 54

    // snaresequencer
    //                        !               !               !               !      
    const char* patternSnr  = "....x.......x.......x.......x.......x.......x.......x.......x..."; 
    const char* patternSnr2 = "....x..x....x....x..x.......x..x....x....x..x.......x..x.x.xx.x."; 
    pattern = snaresequencer->readPattern(patternSnr, 0, 54); // kick 4x4, channel 0, note 54
    snaresequencer->setNextPattern(pattern);
    pattern = snaresequencer->readPattern(patternSnr2, 0, 54); // kick 4x4, channel 0, note 54

    multiseq.start(micros());
    AudioInterrupts();
}

void loop() {
    // put your main code here, to run repeatedly:
    multiseq.tick(micros());

    while (Serial.available()) {
        char inChar = Serial.read();
        switch (inChar) {
            case 'q': kicksequencer->setNextPattern((int)0); break;
            case 'w': kicksequencer->setNextPattern((int)1); break;
            case 'a': snaresequencer->setNextPattern((int)0); break;
            case 's': snaresequencer->setNextPattern((int)1); break;
            default:
                break;
        }
    }
}