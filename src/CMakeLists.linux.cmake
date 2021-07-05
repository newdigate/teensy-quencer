cmake_minimum_required(VERSION 3.5)
set(teensyquencer_VERSION 1.0.1)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include/teensyquencer/)
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/teensyquencer )

find_package(teensy_x86_stubs)
include_directories(${teensy_x86_stubs_INCLUDE_DIR})

find_package(teensy_x86_sd_stubs)
include_directories(${teensy_x86_sd_stubs_INCLUDE_DIR})

add_library(teensyquencer STATIC ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(teensyquencer PROPERTIES PUBLIC_HEADER ${HEADER_FILES})

include(CMakePackageConfigHelpers)
configure_package_config_file(../cmake/teensyquencer.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/teensyquencerConfig.cmake
        INSTALL_DESTINATION ${LIB_INSTALL_DIR}/teensyquencer/cmake
        PATH_VARS)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/teensyquencerConfigVersion.cmake
        VERSION ${teensyquencer_VERSION}
        COMPATIBILITY SameMajorVersion )

install(TARGETS teensyquencer DESTINATION
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        PUBLIC_HEADER DESTINATION "include/teensyquencer"
        )

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/teensyquencerConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/teensyquencerConfigVersion.cmake
        ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/uninstall.cmake
        DESTINATION "lib/cmake/teensyquencer" )
##
# copied from: https://gist.github.com/royvandam/3033428
# Add uninstall target
# Requirements: Copy the uninstall.cmake file to the appropriate CMAKE_MODULE_PATH.
#
set(CMAKE_VERBOSE_MAKEFILE 1)
add_custom_target(installarduino
        "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/install_arduino_library.cmake")

add_custom_target(uninstall
        "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/uninstall.cmake")
