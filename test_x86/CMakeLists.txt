cmake_minimum_required(VERSION 3.5)
project(testteensyquencer CXX)

include_directories(../teensy_cores_x86)
include_directories(../common)

add_executable(testteensyquencer
        runtests.cpp)

target_link_libraries(testteensyquencer teensy_cores_x86)
target_link_libraries(testteensyquencer common)