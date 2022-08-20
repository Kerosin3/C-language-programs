cmake_minimum_required(VERSION 3.14)

project(weather_looker LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(CMAKE_EXE_LINKER_FLAGS "-static") --static link all
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../test) #copy executable

set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS True)
set(CURL_DISABLE_TEST ON)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(sources/curl-7.84.0)

set(ENABLE_CJSON_TEST OFF)
set(BUILD_SHARED_LIBS OFF)
set(ENABLE_CJSON_UNINSTALL OFF)

add_subdirectory(sources/cJSON)

add_subdirectory(sources/main)
message(STATUS "compilation finished, used C standart is:" ${CMAKE_C_STANDARD})

