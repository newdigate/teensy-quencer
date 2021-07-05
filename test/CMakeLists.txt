cmake_minimum_required(VERSION 3.5)
project(testteensyquencer CXX)

include_directories(../src)

add_executable(tests
        runtests.cpp)

target_link_libraries(tests ${teensy_x86_stubs_LIBS})
target_link_libraries(tests ${teensy_audio_x86_stubs_LIBS})
target_link_libraries(tests ${teensy_x86_sd_stubs_LIBS})
target_link_libraries(tests teensyquencer)

