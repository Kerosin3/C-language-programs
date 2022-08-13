cmake_minimum_required(VERSION 3.14)

project(hash_table LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../test) #copy
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_custom_target(
    build_spookyhash ALL
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/sources/spookyhash/build
    COMMAND premake5 gmake
    COMMAND make -f Makefile
    COMMAND cp bin/Release/libspookyhash.a ${PROJECT_SOURCE_DIR}/sources/libs
    COMMENT "===========compiled spookyhash lib============="
    VERBATIM
)

add_subdirectory(sources/main)
add_subdirectory(sources/side)

