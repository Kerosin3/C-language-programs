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
include tests/server/CMakeFiles/rtspd.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/server/CMakeFiles/rtspd.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/server/CMakeFiles/rtspd.dir/progress.make

# Include the compile flags for this target's objects.
include tests/server/CMakeFiles/rtspd.dir/flags.make

tests/server/CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.o: ../lib/mprintf.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/mprintf.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/mprintf.c > CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/mprintf.c -o CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.s

tests/server/CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.o: ../lib/nonblock.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/nonblock.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/nonblock.c > CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/nonblock.c -o CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.s

tests/server/CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.o: ../lib/strtoofft.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/strtoofft.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/strtoofft.c > CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/strtoofft.c -o CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.s

tests/server/CMakeFiles/rtspd.dir/__/__/lib/warnless.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/warnless.c.o: ../lib/warnless.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/warnless.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/warnless.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/warnless.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/warnless.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/warnless.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/warnless.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/warnless.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/warnless.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/warnless.c > CMakeFiles/rtspd.dir/__/__/lib/warnless.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/warnless.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/warnless.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/warnless.c -o CMakeFiles/rtspd.dir/__/__/lib/warnless.c.s

tests/server/CMakeFiles/rtspd.dir/__/__/lib/timediff.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/timediff.c.o: ../lib/timediff.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/timediff.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/timediff.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/timediff.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/timediff.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/timediff.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/timediff.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/timediff.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/timediff.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/timediff.c > CMakeFiles/rtspd.dir/__/__/lib/timediff.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/timediff.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/timediff.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/timediff.c -o CMakeFiles/rtspd.dir/__/__/lib/timediff.c.s

tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.o: ../lib/curl_ctype.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/curl_ctype.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/curl_ctype.c > CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/curl_ctype.c -o CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.s

tests/server/CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.o: ../lib/dynbuf.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/dynbuf.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/dynbuf.c > CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/dynbuf.c -o CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.s

tests/server/CMakeFiles/rtspd.dir/__/__/lib/strdup.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/strdup.c.o: ../lib/strdup.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/strdup.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/strdup.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/strdup.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/strdup.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/strdup.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/strdup.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/strdup.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/strdup.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/strdup.c > CMakeFiles/rtspd.dir/__/__/lib/strdup.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/strdup.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/strdup.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/strdup.c -o CMakeFiles/rtspd.dir/__/__/lib/strdup.c.s

tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.o: ../lib/curl_multibyte.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/curl_multibyte.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/curl_multibyte.c > CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/curl_multibyte.c -o CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.s

tests/server/CMakeFiles/rtspd.dir/getpart.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/getpart.c.o: ../tests/server/getpart.c
tests/server/CMakeFiles/rtspd.dir/getpart.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object tests/server/CMakeFiles/rtspd.dir/getpart.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/getpart.c.o -MF CMakeFiles/rtspd.dir/getpart.c.o.d -o CMakeFiles/rtspd.dir/getpart.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/server/getpart.c

tests/server/CMakeFiles/rtspd.dir/getpart.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/getpart.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/server/getpart.c > CMakeFiles/rtspd.dir/getpart.c.i

tests/server/CMakeFiles/rtspd.dir/getpart.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/getpart.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/server/getpart.c -o CMakeFiles/rtspd.dir/getpart.c.s

tests/server/CMakeFiles/rtspd.dir/__/__/lib/base64.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/base64.c.o: ../lib/base64.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/base64.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/base64.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/base64.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/base64.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/base64.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/base64.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/base64.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/base64.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/base64.c > CMakeFiles/rtspd.dir/__/__/lib/base64.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/base64.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/base64.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/base64.c -o CMakeFiles/rtspd.dir/__/__/lib/base64.c.s

tests/server/CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.o: ../lib/memdebug.c
tests/server/CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object tests/server/CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.o -MF CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.o.d -o CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/memdebug.c

tests/server/CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/memdebug.c > CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.i

tests/server/CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/lib/memdebug.c -o CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.s

tests/server/CMakeFiles/rtspd.dir/util.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/util.c.o: ../tests/server/util.c
tests/server/CMakeFiles/rtspd.dir/util.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object tests/server/CMakeFiles/rtspd.dir/util.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/util.c.o -MF CMakeFiles/rtspd.dir/util.c.o.d -o CMakeFiles/rtspd.dir/util.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/server/util.c

tests/server/CMakeFiles/rtspd.dir/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/util.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/server/util.c > CMakeFiles/rtspd.dir/util.c.i

tests/server/CMakeFiles/rtspd.dir/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/util.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/server/util.c -o CMakeFiles/rtspd.dir/util.c.s

tests/server/CMakeFiles/rtspd.dir/rtspd.c.o: tests/server/CMakeFiles/rtspd.dir/flags.make
tests/server/CMakeFiles/rtspd.dir/rtspd.c.o: ../tests/server/rtspd.c
tests/server/CMakeFiles/rtspd.dir/rtspd.c.o: tests/server/CMakeFiles/rtspd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object tests/server/CMakeFiles/rtspd.dir/rtspd.c.o"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/server/CMakeFiles/rtspd.dir/rtspd.c.o -MF CMakeFiles/rtspd.dir/rtspd.c.o.d -o CMakeFiles/rtspd.dir/rtspd.c.o -c /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/server/rtspd.c

tests/server/CMakeFiles/rtspd.dir/rtspd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtspd.dir/rtspd.c.i"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/server/rtspd.c > CMakeFiles/rtspd.dir/rtspd.c.i

tests/server/CMakeFiles/rtspd.dir/rtspd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtspd.dir/rtspd.c.s"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/server/rtspd.c -o CMakeFiles/rtspd.dir/rtspd.c.s

# Object files for target rtspd
rtspd_OBJECTS = \
"CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.o" \
"CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.o" \
"CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.o" \
"CMakeFiles/rtspd.dir/__/__/lib/warnless.c.o" \
"CMakeFiles/rtspd.dir/__/__/lib/timediff.c.o" \
"CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.o" \
"CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.o" \
"CMakeFiles/rtspd.dir/__/__/lib/strdup.c.o" \
"CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.o" \
"CMakeFiles/rtspd.dir/getpart.c.o" \
"CMakeFiles/rtspd.dir/__/__/lib/base64.c.o" \
"CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.o" \
"CMakeFiles/rtspd.dir/util.c.o" \
"CMakeFiles/rtspd.dir/rtspd.c.o"

# External object files for target rtspd
rtspd_EXTERNAL_OBJECTS =

tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/mprintf.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/nonblock.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/strtoofft.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/warnless.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/timediff.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_ctype.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/dynbuf.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/strdup.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/curl_multibyte.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/getpart.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/base64.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/__/__/lib/memdebug.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/util.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/rtspd.c.o
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/build.make
tests/server/rtspd: /usr/lib/libssl.so
tests/server/rtspd: /usr/lib/libcrypto.so
tests/server/rtspd: /usr/lib/libz.so
tests/server/rtspd: /usr/lib/libpsl.so
tests/server/rtspd: /usr/lib/libssh2.so
tests/server/rtspd: tests/server/CMakeFiles/rtspd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking C executable rtspd"
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rtspd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/server/CMakeFiles/rtspd.dir/build: tests/server/rtspd
.PHONY : tests/server/CMakeFiles/rtspd.dir/build

tests/server/CMakeFiles/rtspd.dir/clean:
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server && $(CMAKE_COMMAND) -P CMakeFiles/rtspd.dir/cmake_clean.cmake
.PHONY : tests/server/CMakeFiles/rtspd.dir/clean

tests/server/CMakeFiles/rtspd.dir/depend:
	cd /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0 /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/tests/server /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server /home/ker0/test/C_lang/weather_looker/sources/curl-7.84.0/build/tests/server/CMakeFiles/rtspd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/server/CMakeFiles/rtspd.dir/depend

