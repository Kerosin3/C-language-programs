cmake_minimum_required(VERSION 3.14)

project(debug_logger_lib LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(C_EXTENSIONS FALSE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-rdynamic -O3")

set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors ")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
add_subdirectory(sources)

