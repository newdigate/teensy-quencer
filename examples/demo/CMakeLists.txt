cmake_minimum_required(VERSION 3.5)
project(example_demo CXX)
set(CMAKE_VERBOSE_MAKEFILE 1)
teensy_include_directories(../../src)
teensy_add_executable(example_demo teensy-quencer.ino)    
teensy_target_link_libraries(example_demo  teensypolyphony midismfreader teensyquencer tftpianoview TeensyVariablePlayback Audio arm_math SD SdFat  ST7735_t3 SPI SerialFlash  Wire  USBHost_t36 cores)    
target_link_libraries(example_demo.elf m stdc++)

