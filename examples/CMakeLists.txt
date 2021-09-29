cmake_minimum_required(VERSION 3.5)
project(examples)

import_arduino_library(teensypolyphony ${DEPSPATH}/teensy-polyphony/src)

add_subdirectory(audioshield)
add_subdirectory(basic)
add_subdirectory(demo)
