cmake_minimum_required(VERSION 3.5)
project(teensysequencer CXX)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory( teensy_cores_x86 )
add_subdirectory(src)
add_subdirectory( test_x86 )