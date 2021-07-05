cmake_minimum_required(VERSION 3.5)

project(teensyquencer C CXX)

set(SOURCE_FILES
		midireader.cpp midisequenceadapter.cpp polyphonicsampler.cpp)

set(HEADER_FILES
		sequencer.h sequencer.cpp tempo.h songposition.h midireader.h midisequenceadapter.h polyphonicsampler.h)

if (DEFINED BUILD_FOR_LINUX)    
	include(CMakeLists.linux.cmake)
else()
	include(CMakeLists.teensy.cmake)
endif()