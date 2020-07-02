#include <stdint.h>
#include <iostream>
#include "SD/SD.h"
#include <unistd.h>
#include <dirent.h>
#include "../common/sequencer.h"
using namespace std;

void millis_test();
void delay_test();
void first_test();

int main(int argc, char **argv){
    std::cout << "starting app...\n";
    initialize_mock_arduino();
    first_test();
    std::cout << "complete...\n";
}

void first_test() {
    tempo tempo(120.0f);
    songposition position;
    sequencer sequencer(tempo, position);
    sequencer.onevent = [&] (sequencerevent *event) {
        Serial.printf("%d:%d:%4f\n", position.bar, position.beat, position.sixtyFourth / 64.0f);
        Serial.printf("----- %d:%d:%4f\n", event->channel, event->isNoteStartEvent, event->rate);
    };

  for (int i=0; i < 16; i++) {
      loopelement *kick = new loopelement();
      kick->rate = 1.0f;
      kick->start_tick = (i * 16 * 4);
      kick->stop_tick = (i * 16 * 4) + 15;
      kick->channel = 2;
      kick->loopType = looptypex_none;
      sequencer.addelement(kick);
  }

  for (int i=0; i < 16; i++) {
      loopelement *kick = new loopelement();
      kick->rate = 1.0f;
      kick->start_tick = ((i+2) * 16 * 4);
      kick->stop_tick = ((i+2) * 16 * 4) + 15;
      kick->channel = 3;
      kick->loopType = looptypex_none;
      sequencer.addelement(kick);
  }

  for (int i=0; i < 32; i++) {
      loopelement *snare = new loopelement();
      snare->rate = 1.0f;
      snare->start_tick = ((i+2) * 8 * 4);
      snare->stop_tick = ((i+2) * 8 * 4) + 15;
      snare->channel = 1;
      snare->loopType = looptypex_none;
      sequencer.addelement(snare);
  }

    sequencer.writescore();
  return;
    sequencer.start(millis());
   // sequencer.tick(0);
   // sequencer.tick(250);
  //  sequencer.tick(500);
  //  sequencer.tick(750);
  //  sequencer.tick(1000);
  //  sequencer.tick(1250);
  //  sequencer.tick(1500);

    while (true) {
       sequencer.tick(millis());
       //Serial.printf("%d:%d:%4f\n", position.bar, position.beat, position.sixtyFourth / 64.0f);
       delay(5);
    }
    for (int i=0; i<8; i++) {
       sequencer.tick(millis());
       delay(20);
    }
}

void millis_test() {
  unsigned long start = millis();
  cout << "millis() test start: " << start << endl;
  while( millis() - start < 10000 ) {
	cout << millis() << endl;
	delay(1);
  }
  unsigned long end = millis();
  cout << "End of test - duration: " << end - start << "ms" << endl;
}

void delay_test() {
  unsigned long start = millis();
  cout << "delay() test start: " << start << endl;
  while( millis() - start < 10000 ) {
	cout << millis() << endl;
	delay(250);
  }
  unsigned long end = millis();
  cout << "End of test - duration: " << end - start << "ms" << endl;
}