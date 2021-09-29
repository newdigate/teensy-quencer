cmake_minimum_required(VERSION 3.10)
project(audioshield)

set(CMAKE_CXX_STANDARD 11)
teensy_include_directories(../../src)
teensy_add_executable(audioshield audioshield.ino)
teensy_target_link_libraries(audioshield teensyquencer Audio arm_math SD SdFat  ST7735_t3 SPI SerialFlash  Wire  cores)    
target_link_libraries(audioshield.elf m stdc++)