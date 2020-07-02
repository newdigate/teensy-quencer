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
AudioPlaySdRawResampled  playSdRaw1;     //xy=324,457
AudioOutputI2S           i2s2;           //xy=840.8571472167969,445.5714416503906
AudioConnection          patchCord1(playSdRaw1, 0, i2s2, 0);
AudioConnection          patchCord2(playSdRaw1, 0, i2s2, 1);
// GUItool: end automatically generated code

void setup() {

  Serial.begin(57600);
  delay(5);
  while (!Serial) { yield(); }

    sequencer.onevent = [&] (sequencerevent *event) {
        Serial.printf("%d:%d:%4f\n", position.bar, position.beat, position.sixtyFourth / 64.0f);
        Serial.printf("----- %d:%d:%4f\n", event->channel, event->isNoteStartEvent, event->rate);
    };

    for (int i=0; i < 4; i++) {
        loopelement *kick = new loopelement();
        kick->rate = 1.0f;
        kick->start_tick = (i * 64 * 4);
        kick->stop_tick = (i * 64 * 4) + 63;
        kick->channel = 1;
        kick->loopType = looptypex_none;
        sequencer.addelement(kick);
    }

    for (int i=0; i < 16; i++) {
        loopelement *snare = new loopelement();
        snare->rate = 1.0f;
        snare->start_tick = ((i+1) * 16 * 4);
        snare->stop_tick = ((i+1) * 16 * 4) + 15;
        snare->channel = 2;
        snare->loopType = looptypex_none;
        sequencer.addelement(snare);
    }
    sequencer.start(millis());

}

void loop() {
  // put your main code here, to run repeatedly:
  sequencer.tick(millis());
}

unsigned __exidx_start;
unsigned __exidx_end;
