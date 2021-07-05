cmake_minimum_required(VERSION 3.10)
project(basic)

set(CMAKE_CXX_STANDARD 11)
teensy_include_directories(../../src)
teensy_add_executable(example_demo midiread.cpp)
teensy_target_link_libraries(example_demo  teensyquencer tftpianoview TeensyVariablePlayback Audio  SD SdFat  ST7735_t3 SPI SerialFlash  Wire  USBHost_t36 cores)    
target_link_libraries(example_demo.elf m stdc++)