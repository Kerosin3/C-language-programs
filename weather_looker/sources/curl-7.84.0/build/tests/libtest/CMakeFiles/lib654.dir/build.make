# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build

# Include any dependencies generated for this target.
include tests/libtest/CMakeFiles/lib654.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/libtest/CMakeFiles/lib654.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/libtest/CMakeFiles/lib654.dir/progress.make

# Include the compile flags for this target's objects.
include tests/libtest/CMakeFiles/lib654.dir/flags.make

tests/libtest/CMakeFiles/lib654.dir/lib654.c.o: tests/libtest/CMakeFiles/lib654.dir/flags.make
tests/libtest/CMakeFiles/lib654.dir/lib654.c.o: ../tests/libtest/lib654.c
tests/libtest/CMakeFiles/lib654.dir/lib654.c.o: tests/libtest/CMakeFiles/lib654.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/libtest/CMakeFiles/lib654.dir/lib654.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/libtest/CMakeFiles/lib654.dir/lib654.c.o -MF CMakeFiles/lib654.dir/lib654.c.o.d -o CMakeFiles/lib654.dir/lib654.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/libtest/lib654.c

tests/libtest/CMakeFiles/lib654.dir/lib654.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib654.dir/lib654.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/libtest/lib654.c > CMakeFiles/lib654.dir/lib654.c.i

tests/libtest/CMakeFiles/lib654.dir/lib654.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib654.dir/lib654.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/libtest/lib654.c -o CMakeFiles/lib654.dir/lib654.c.s

tests/libtest/CMakeFiles/lib654.dir/__/__/lib/timediff.c.o: tests/libtest/CMakeFiles/lib654.dir/flags.make
tests/libtest/CMakeFiles/lib654.dir/__/__/lib/timediff.c.o: ../lib/timediff.c
tests/libtest/CMakeFiles/lib654.dir/__/__/lib/timediff.c.o: tests/libtest/CMakeFiles/lib654.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/libtest/CMakeFiles/lib654.dir/__/__/lib/timediff.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/libtest/CMakeFiles/lib654.dir/__/__/lib/timediff.c.o -MF CMakeFiles/lib654.dir/__/__/lib/timediff.c.o.d -o CMakeFiles/lib654.dir/__/__/lib/timediff.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/timediff.c

tests/libtest/CMakeFiles/lib654.dir/__/__/lib/timediff.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib654.dir/__/__/lib/timediff.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/timediff.c > CMakeFiles/lib654.dir/__/__/lib/timediff.c.i

tests/libtest/CMakeFiles/lib654.dir/__/__/lib/timediff.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib654.dir/__/__/lib/timediff.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/timediff.c -o CMakeFiles/lib654.dir/__/__/lib/timediff.c.s

tests/libtest/CMakeFiles/lib654.dir/first.c.o: tests/libtest/CMakeFiles/lib654.dir/flags.make
tests/libtest/CMakeFiles/lib654.dir/first.c.o: ../tests/libtest/first.c
tests/libtest/CMakeFiles/lib654.dir/first.c.o: tests/libtest/CMakeFiles/lib654.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tests/libtest/CMakeFiles/lib654.dir/first.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/libtest/CMakeFiles/lib654.dir/first.c.o -MF CMakeFiles/lib654.dir/first.c.o.d -o CMakeFiles/lib654.dir/first.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/libtest/first.c

tests/libtest/CMakeFiles/lib654.dir/first.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib654.dir/first.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/libtest/first.c > CMakeFiles/lib654.dir/first.c.i

tests/libtest/CMakeFiles/lib654.dir/first.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib654.dir/first.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/libtest/first.c -o CMakeFiles/lib654.dir/first.c.s

# Object files for target lib654
lib654_OBJECTS = \
"CMakeFiles/lib654.dir/lib654.c.o" \
"CMakeFiles/lib654.dir/__/__/lib/timediff.c.o" \
"CMakeFiles/lib654.dir/first.c.o"

# External object files for target lib654
lib654_EXTERNAL_OBJECTS =

tests/libtest/lib654: tests/libtest/CMakeFiles/lib654.dir/lib654.c.o
tests/libtest/lib654: tests/libtest/CMakeFiles/lib654.dir/__/__/lib/timediff.c.o
tests/libtest/lib654: tests/libtest/CMakeFiles/lib654.dir/first.c.o
tests/libtest/lib654: tests/libtest/CMakeFiles/lib654.dir/build.make
tests/libtest/lib654: lib/libcurl.so
tests/libtest/lib654: /usr/lib/libssl.so
tests/libtest/lib654: /usr/lib/libcrypto.so
tests/libtest/lib654: /usr/lib/libz.so
tests/libtest/lib654: /usr/lib/libpsl.so
tests/libtest/lib654: /usr/lib/libssh2.so
tests/libtest/lib654: tests/libtest/CMakeFiles/lib654.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable lib654"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib654.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/libtest/CMakeFiles/lib654.dir/build: tests/libtest/lib654
.PHONY : tests/libtest/CMakeFiles/lib654.dir/build

tests/libtest/CMakeFiles/lib654.dir/clean:
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest && $(CMAKE_COMMAND) -P CMakeFiles/lib654.dir/cmake_clean.cmake
.PHONY : tests/libtest/CMakeFiles/lib654.dir/clean

tests/libtest/CMakeFiles/lib654.dir/depend:
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0 /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/libtest /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/libtest/CMakeFiles/lib654.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/libtest/CMakeFiles/lib654.dir/depend

