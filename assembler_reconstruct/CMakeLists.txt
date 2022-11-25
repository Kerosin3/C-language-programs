cmake_minimum_required(VERSION 3.14)

project(ASM_PRJ LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O0")

set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors ")

ADD_EXECUTABLE (app.out
		main.c)
