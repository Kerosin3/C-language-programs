cmake_minimum_required(VERSION 3.14)

project(http_server LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(C_EXTENSIONS FALSE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_REQUIRED_DEFINITIONS -D_GNU_SOURCE) 
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors ")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
add_subdirectory(sources/contrib)
add_subdirectory(sources/main)

