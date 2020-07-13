#include <stdint.h>
#include <iostream>
#include "SD/SD.h"
#include <unistd.h>
#include <dirent.h>
#include "../common/sequencer.h"
#include "../common/midireader.h"
using namespace std;

void millis_test();
void delay_test();
void first_test();
void second_test();
void midireader_test();

streampos readFileData(string filename, char *&buffer);

int main(int argc, char **argv){
    std::cout << "starting app...\n";
    initialize_mock_arduino();
    midireader_test();
    std::cout << "complete...\n";
}

void first_test() {
    tempo tempo(120.0f);
    songposition *position = new songposition();
    sequencer sequencer(tempo, position);
    sequencer.onevent = [&] (sequencerevent *event) {
        Serial.printf("%d:%d:%4f\n", position->bar, position->beat, position->sixtyFourth / 64.0f);
        Serial.printf("----- %d:%d:%4f\n", event->channel, event->isNoteStartEvent, event->rate);
    };

    sequencer.addPattern(4);

    for (int i=0; i < 16; i++) {
      loopelement *kick = new loopelement();
      kick->rate = 1.0f;
      kick->start_tick = (i * 16 * 4);
      kick->stop_tick = (i * 16 * 4) + 15;
      kick->channel = 2;
      kick->loopType = looptypex_none;
      sequencer.addelement(0, kick);
  }

  for (int i=0; i < 16; i++) {
      loopelement *kick = new loopelement();
      kick->rate = 1.0f;
      kick->start_tick = ((i+2) * 16 * 4);
      kick->stop_tick = ((i+2) * 16 * 4) + 15;
      kick->channel = 3;
      kick->loopType = looptypex_none;
      sequencer.addelement(0, kick);
  }

  for (int i=0; i < 32; i++) {
      loopelement *snare = new loopelement();
      snare->rate = 1.0f;
      snare->start_tick = ((i+2) * 8 * 4);
      snare->stop_tick = ((i+2) * 8 * 4) + 15;
      snare->channel = 1;
      snare->loopType = looptypex_none;
      sequencer.addelement(0, snare);
  }

    sequencer.writescore(0);
  //return;
    sequencer.start(micros());
   // sequencer.tick(0);
   // sequencer.tick(250);
  //  sequencer.tick(500);
  //  sequencer.tick(750);
  //  sequencer.tick(1000);
  //  sequencer.tick(1250);
  //  sequencer.tick(1500);

    while (true) {
       sequencer.tick(micros());
       //Serial.printf("%d:%d:%4f\n", position.bar, position.beat, position.sixtyFourth / 64.0f);
       delay(5);
    }
    for (int i=0; i<8; i++) {
       sequencer.tick(micros());
       delay(20);
    }
}

void second_test() {
    tempo tempo(120.0f);

    multisequencer multisequencer(tempo);

    sequencer *sequencer = multisequencer.newSequencer();
    
    sequencer->onevent = [&] (sequencerevent *event) {
        //Serial.printf("%d:%d:%4f\n", position.bar, position.beat, position.sixtyFourth / 64.0f);
        Serial.printf("----- %d:%d:%4f\n", event->channel, event->isNoteStartEvent, event->rate);
    };

    sequencer->addPattern(4);

    for (int i=0; i < 16; i++) {
      loopelement *kick = new loopelement();
      kick->rate = 1.0f;
      kick->start_tick = (i * 16 * 4);
      kick->stop_tick = (i * 16 * 4) + 15;
      kick->channel = 2;
      kick->loopType = looptypex_none;
      sequencer->addelement(0, kick);
  }

  for (int i=0; i < 16; i++) {
      loopelement *kick = new loopelement();
      kick->rate = 1.0f;
      kick->start_tick = ((i+2) * 16 * 4);
      kick->stop_tick = ((i+2) * 16 * 4) + 15;
      kick->channel = 3;
      kick->loopType = looptypex_none;
      sequencer->addelement(0, kick);
  }

  for (int i=0; i < 32; i++) {
      loopelement *snare = new loopelement();
      snare->rate = 1.0f;
      snare->start_tick = ((i+2) * 8 * 4);
      snare->stop_tick = ((i+2) * 8 * 4) + 15;
      snare->channel = 1;
      snare->loopType = looptypex_none;
      sequencer->addelement(0, snare);
  }

    sequencer->writescore(0);
  //return;
    multisequencer.start(micros());
   // sequencer.tick(0);
   // sequencer.tick(250);
  //  sequencer.tick(500);
  //  sequencer.tick(750);
  //  sequencer.tick(1000);
  //  sequencer.tick(1250);
  //  sequencer.tick(1500);

    while (true) {
       multisequencer.tick(micros());
       //Serial.printf("%d:%d:%4f\n", position.bar, position.beat, position.sixtyFourth / 64.0f);
       delay(5);
    }
}

void search(std::string curr_directory, std::string extension, vector<string> &results){
	DIR* dir_point = opendir(curr_directory.c_str());
	dirent* entry = readdir(dir_point);
	while (entry){									// if !entry then end of directory
		if (entry->d_type == DT_DIR){				// if entry is a directory
			std::string fname = entry->d_name;
			if (fname != "." && fname != "..")
				search(entry->d_name, extension, results);	// search through it
		}
		else if (entry->d_type == DT_REG){		// if entry is a regular file
			std::string fname = entry->d_name;	// filename
      // if filename's last characters are extension
			if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos)
				results.push_back(fname);		// add filename to results vector
		}
		entry = readdir(dir_point);
	}
	return;
}

void midireader_test() {
    std::vector<std::string> midiFiles;				// holds search results
    string midiFileDirectory = "/Users/xxx/Development/SD";
    search(midiFileDirectory,"mid", midiFiles);

    std::cout << midiFiles.size() << " files were found:" << std::endl;
		for (unsigned int i = 0; i < midiFiles.size(); ++i)	 { // used unsigned to appease compiler warnings
        std::cout << midiFiles[i] << std::endl;

        char *buffer;
        std::string midiFileName = midiFileDirectory + "/" + midiFiles[i];
        streampos bytesRead = readFileData(midiFileName, buffer);
        if (bytesRead > 0) {
            SD.setSDCardFileData(buffer, bytesRead);

            midireader reader;
            reader.open("Dread.mid");
            for (int i = 0; i < reader.getNumTracks(); i++) {
                midimessage message;
                reader.setTrackNumber(i);
                while (reader.read(message)) {
                    //Serial.printf("status: %x, channel:%x\n", message.status, message.channel);
                }
                Serial.printf("track end: %d;\n", i);
            }
            Serial.printf("song end");
        }
        delete buffer;
    }
}

streampos readFileData(string filename, char *&buffer) {
    fstream mockFile = fstream();
    mockFile.open(filename, ios_base::in | ios_base::binary | ios_base::ate);
    if (mockFile.is_open()) {
        streampos bytesRead = mockFile.tellg();
        buffer = new char[bytesRead];
        mockFile.seekg(0, ios_base::beg);
        mockFile.read(buffer, bytesRead);
        return bytesRead;
    }
    return 0;
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