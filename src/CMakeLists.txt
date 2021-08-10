cmake_minimum_required(VERSION 3.5)

project(teensyquencer C CXX)

set(SOURCE_FILES
		midisequenceadapter.cpp sequencer.cpp)

set(HEADER_FILES
		Teensyquencer.h sequencer.h tempo.h songposition.h midisequenceadapter.h)

if (NOT DEFINED TEENSY_VERSION)    
	include(CMakeLists.linux.cmake)
else()
	include(CMakeLists.teensy.cmake)
endif()