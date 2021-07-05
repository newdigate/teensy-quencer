teensy_add_library(teensyquencer ${SOURCE_FILES})

add_custom_target(installarduino
"${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/install_arduino_library.cmake")