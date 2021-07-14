cmake_minimum_required(VERSION 3.5)

project(teensyquencer C CXX)

set(SOURCE_FILES
		midisequenceadapter.cpp polyphonicsampler.cpp sequencer.cpp)

set(HEADER_FILES
		sequencer.h tempo.h songposition.h midisequenceadapter.h polyphonicsampler.h)

if (NOT DEFINED TEENSY_VERSION)    
	include(CMakeLists.linux.cmake)
else()
	include(CMakeLists.teensy.cmake)
endif()