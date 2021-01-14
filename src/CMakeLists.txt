cmake_minimum_required(VERSION 3.5)

project(common C CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(teensy_x86_stubs)
include_directories(${teensy_x86_stubs_INCLUDE_DIR})

find_package(midi_smf_reader)
include_directories(${midi_smf_reader_INCLUDE_DIR})

add_library(common STATIC
		sequencer.h sequencer.cpp tempo.h songposition.h midisequenceadapter.cpp midisequenceadapter.h polyphonicsampler.cpp polyphonicsampler.h)
