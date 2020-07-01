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
    
    loopelement *element1 = new loopelement();
    element1->rate = 1.0f;
    element1->start_tick = 64;
    element1->stop_tick = 256;
    element1->channel = 2;
    element1->loopType = looptype_none;
    sequencer.addelement(element1);

    sequencer.start();
    while (true) {
       sequencer.tick(millis());
       //Serial.printf("%d:%d:%4f\n", position.bar, position.beat, position.sixtyFourth / 64.0f);
       delay(50);
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