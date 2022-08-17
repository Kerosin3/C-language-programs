cmake_minimum_required(VERSION 3.14)

project(weather_looker LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors")
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../test) #copy
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_EXE_LINKER_FLAGS "-static")

#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)

#add_subdirectory(sources/curl-7.84.0)

set(ENABLE_CJSON_TEST OFF)
#set(DBUILD_SHARED_AND_STATIC_LIBS OFF)
set(BUILD_SHARED_LIBS OFF)
set(ENABLE_CJSON_UNINSTALL OFF)

add_subdirectory(sources/cJSON)

add_subdirectory(sources/main)
message(STATUS "used C standart is:" ${CMAKE_C_STANDARD})

