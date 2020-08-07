cmake_minimum_required(VERSION 3.5)

project(common C CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(common STATIC
		sequencer.h sequencer.cpp tempo.h songposition.h midireader.h midireader.cpp midisequenceadapter.cpp midisequenceadapter.h polyphonicsampler.cpp polyphonicsampler.h)
