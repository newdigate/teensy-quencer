# teensyquencer
my attemp to make a little sequencer using teensy audio library... work in progress!!!

## code
* define multisequencer:
```
tempo tempo(120.0f);
multisequencer multisequencer(tempo);
```

* add sequencer channel:
```
  sequencer *sequencer = multisequencer.newSequencer();
```

* add event callbacks:
```
  sequencer->onevent = [] (sequencerevent *event) {
      switch(event->channel) {
        case 0: triggerAudioEvent(event, playSdRaw1, "KICK.WAV"); break;
        case 1: triggerAudioEvent(event, playSdRaw2, "SNARE.WAV"); break;      
        default: break;
      }
  };
```
* add pattern:
```

  //                        !               !               !               !      
  const char* pattern4x4 = "X...X...X...X...X...X...X...X...X...X...X...X...X...X...X...X..."; 
  const char* patternSnr = "....x.......x.......x.......x.......x.......x.......x.......x..."; 

  int pattern = 0;

  sequencer->addPattern(); // empty pattern
  pattern++;
  
  beatsequencer->addPattern(); // kick solo 4 x 4
  readPattern(0, pattern, pattern4x4, sequencer); //kick
  pattern++;

  beatsequencer->addPattern(); // kick solo 4 x 4 + snare
  readPattern(0, pattern, pattern4x4, sequencer); //kick
  readPattern(1, pattern, patternSnr, sequencer); //snare
  pattern++;
```

## compiling for teensy
You will need to add c++ std library to your compiler flags in boards.txt (Teensyduino/Java/hardware/teensy/avr/boards.txt)
* remove -nostdlib from teensy40.build.flags.common
* add -lstdc++ to teensy40.build.flags.cpp
```
teensy40.build.flags.common=-g -Wall -ffunction-sections -fdata-sections
teensy40.build.flags.cpp=-std=gnu++14 -fno-exceptions -fpermissive -fno-rtti -fno-threadsafe-statics -felide-constructors -Wno-error=narrowing -lstdc++
```

