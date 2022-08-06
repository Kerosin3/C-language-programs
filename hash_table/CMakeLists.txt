cmake_minimum_required(VERSION 3.8)

project(hash_table LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_PATH}/output/${CMAKE_BUILD_TYPE})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_PATH}/output)

add_subdirectory(sources/main)
add_subdirectory(sources/side)
