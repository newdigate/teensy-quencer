#include "common/sequencer.h"
#include "common/songposition.h"
#include "common/tempo.h"

tempo tempo(120.0f);
songposition position;
sequencer sequencer(tempo, position);

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
        kick->loopType = looptype_none;
        sequencer.addelement(kick);
    }

    for (int i=0; i < 16; i++) {
        loopelement *snare = new loopelement();
        snare->rate = 1.0f;
        snare->start_tick = ((i+1) * 16 * 4);
        snare->stop_tick = ((i+1) * 16 * 4) + 15;
        snare->channel = 2;
        snare->loopType = looptype_none;
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
