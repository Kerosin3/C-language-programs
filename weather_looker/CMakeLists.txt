cmake_minimum_required(VERSION 3.14)

project(weather_looker LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors")
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../test) #copy
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(sources/main)
add_subdirectory(sources/side)

