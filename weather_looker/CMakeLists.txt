cmake_minimum_required(VERSION 3.14)

project(weather_looker LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors")
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../test) #copy
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(BUILD_CURL_EXE OFF)
set(BUILD_SHARED_LIBS OFF)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)

add_subdirectory(sources/curl-7.84.0)
add_subdirectory(sources/main)
message(STATUS "asdasdad" ${CMAKE_C_STANDARD})

