cmake_minimum_required(VERSION 3.5)
project(testteensyquencer CXX)

include_directories(../src)

find_package(teensy_x86_stubs)
include_directories(${teensy_x86_stubs_INCLUDE_DIR})
message(STATUS "include-dir: teensy_x86_stubs: ${teensy_x86_stubs_INCLUDE_DIR}")

find_package(midi_smf_reader)
include_directories(${midi_smf_reader_INCLUDE_DIR})
message(STATUS "include-dir: midi_smf_reader: ${midi_smf_reader_INCLUDE_DIR}")

add_executable(testteensyquencer
        runtests.cpp)

target_link_libraries(testteensyquencer ${teensy_x86_stubs_LIBS})
message(STATUS "link: teensy_x86_stubs: ${teensy_x86_stubs_LIBS}")
target_link_libraries(testteensyquencer ${midi_smf_reader_LIBS})
message(STATUS "link: midi_smf_reader: ${midi_smf_reader_LIBS}")
