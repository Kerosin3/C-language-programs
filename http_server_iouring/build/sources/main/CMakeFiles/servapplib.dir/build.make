# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/ker0/test/C_lang/http_server_iouring

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ker0/test/C_lang/http_server_iouring/build

# Include any dependencies generated for this target.
include sources/main/CMakeFiles/servapplib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include sources/main/CMakeFiles/servapplib.dir/compiler_depend.make

# Include the progress variables for this target.
include sources/main/CMakeFiles/servapplib.dir/progress.make

# Include the compile flags for this target's objects.
include sources/main/CMakeFiles/servapplib.dir/flags.make

sources/main/CMakeFiles/servapplib.dir/bufandfiles.c.o: sources/main/CMakeFiles/servapplib.dir/flags.make
sources/main/CMakeFiles/servapplib.dir/bufandfiles.c.o: /home/ker0/test/C_lang/http_server_iouring/sources/main/bufandfiles.c
sources/main/CMakeFiles/servapplib.dir/bufandfiles.c.o: sources/main/CMakeFiles/servapplib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/http_server_iouring/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object sources/main/CMakeFiles/servapplib.dir/bufandfiles.c.o"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT sources/main/CMakeFiles/servapplib.dir/bufandfiles.c.o -MF CMakeFiles/servapplib.dir/bufandfiles.c.o.d -o CMakeFiles/servapplib.dir/bufandfiles.c.o -c /home/ker0/test/C_lang/http_server_iouring/sources/main/bufandfiles.c

sources/main/CMakeFiles/servapplib.dir/bufandfiles.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servapplib.dir/bufandfiles.c.i"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/http_server_iouring/sources/main/bufandfiles.c > CMakeFiles/servapplib.dir/bufandfiles.c.i

sources/main/CMakeFiles/servapplib.dir/bufandfiles.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servapplib.dir/bufandfiles.c.s"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/http_server_iouring/sources/main/bufandfiles.c -o CMakeFiles/servapplib.dir/bufandfiles.c.s

sources/main/CMakeFiles/servapplib.dir/event_loop.c.o: sources/main/CMakeFiles/servapplib.dir/flags.make
sources/main/CMakeFiles/servapplib.dir/event_loop.c.o: /home/ker0/test/C_lang/http_server_iouring/sources/main/event_loop.c
sources/main/CMakeFiles/servapplib.dir/event_loop.c.o: sources/main/CMakeFiles/servapplib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/http_server_iouring/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object sources/main/CMakeFiles/servapplib.dir/event_loop.c.o"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT sources/main/CMakeFiles/servapplib.dir/event_loop.c.o -MF CMakeFiles/servapplib.dir/event_loop.c.o.d -o CMakeFiles/servapplib.dir/event_loop.c.o -c /home/ker0/test/C_lang/http_server_iouring/sources/main/event_loop.c

sources/main/CMakeFiles/servapplib.dir/event_loop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servapplib.dir/event_loop.c.i"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/http_server_iouring/sources/main/event_loop.c > CMakeFiles/servapplib.dir/event_loop.c.i

sources/main/CMakeFiles/servapplib.dir/event_loop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servapplib.dir/event_loop.c.s"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/http_server_iouring/sources/main/event_loop.c -o CMakeFiles/servapplib.dir/event_loop.c.s

sources/main/CMakeFiles/servapplib.dir/misc.c.o: sources/main/CMakeFiles/servapplib.dir/flags.make
sources/main/CMakeFiles/servapplib.dir/misc.c.o: /home/ker0/test/C_lang/http_server_iouring/sources/main/misc.c
sources/main/CMakeFiles/servapplib.dir/misc.c.o: sources/main/CMakeFiles/servapplib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/http_server_iouring/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object sources/main/CMakeFiles/servapplib.dir/misc.c.o"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT sources/main/CMakeFiles/servapplib.dir/misc.c.o -MF CMakeFiles/servapplib.dir/misc.c.o.d -o CMakeFiles/servapplib.dir/misc.c.o -c /home/ker0/test/C_lang/http_server_iouring/sources/main/misc.c

sources/main/CMakeFiles/servapplib.dir/misc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servapplib.dir/misc.c.i"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/http_server_iouring/sources/main/misc.c > CMakeFiles/servapplib.dir/misc.c.i

sources/main/CMakeFiles/servapplib.dir/misc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servapplib.dir/misc.c.s"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/http_server_iouring/sources/main/misc.c -o CMakeFiles/servapplib.dir/misc.c.s

sources/main/CMakeFiles/servapplib.dir/setup.c.o: sources/main/CMakeFiles/servapplib.dir/flags.make
sources/main/CMakeFiles/servapplib.dir/setup.c.o: /home/ker0/test/C_lang/http_server_iouring/sources/main/setup.c
sources/main/CMakeFiles/servapplib.dir/setup.c.o: sources/main/CMakeFiles/servapplib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/http_server_iouring/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object sources/main/CMakeFiles/servapplib.dir/setup.c.o"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT sources/main/CMakeFiles/servapplib.dir/setup.c.o -MF CMakeFiles/servapplib.dir/setup.c.o.d -o CMakeFiles/servapplib.dir/setup.c.o -c /home/ker0/test/C_lang/http_server_iouring/sources/main/setup.c

sources/main/CMakeFiles/servapplib.dir/setup.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servapplib.dir/setup.c.i"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/http_server_iouring/sources/main/setup.c > CMakeFiles/servapplib.dir/setup.c.i

sources/main/CMakeFiles/servapplib.dir/setup.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servapplib.dir/setup.c.s"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/http_server_iouring/sources/main/setup.c -o CMakeFiles/servapplib.dir/setup.c.s

sources/main/CMakeFiles/servapplib.dir/connection_handlers.c.o: sources/main/CMakeFiles/servapplib.dir/flags.make
sources/main/CMakeFiles/servapplib.dir/connection_handlers.c.o: /home/ker0/test/C_lang/http_server_iouring/sources/main/connection_handlers.c
sources/main/CMakeFiles/servapplib.dir/connection_handlers.c.o: sources/main/CMakeFiles/servapplib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/http_server_iouring/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object sources/main/CMakeFiles/servapplib.dir/connection_handlers.c.o"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT sources/main/CMakeFiles/servapplib.dir/connection_handlers.c.o -MF CMakeFiles/servapplib.dir/connection_handlers.c.o.d -o CMakeFiles/servapplib.dir/connection_handlers.c.o -c /home/ker0/test/C_lang/http_server_iouring/sources/main/connection_handlers.c

sources/main/CMakeFiles/servapplib.dir/connection_handlers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servapplib.dir/connection_handlers.c.i"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/http_server_iouring/sources/main/connection_handlers.c > CMakeFiles/servapplib.dir/connection_handlers.c.i

sources/main/CMakeFiles/servapplib.dir/connection_handlers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servapplib.dir/connection_handlers.c.s"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/http_server_iouring/sources/main/connection_handlers.c -o CMakeFiles/servapplib.dir/connection_handlers.c.s

# Object files for target servapplib
servapplib_OBJECTS = \
"CMakeFiles/servapplib.dir/bufandfiles.c.o" \
"CMakeFiles/servapplib.dir/event_loop.c.o" \
"CMakeFiles/servapplib.dir/misc.c.o" \
"CMakeFiles/servapplib.dir/setup.c.o" \
"CMakeFiles/servapplib.dir/connection_handlers.c.o"

# External object files for target servapplib
servapplib_EXTERNAL_OBJECTS =

sources/main/libservapplib.a: sources/main/CMakeFiles/servapplib.dir/bufandfiles.c.o
sources/main/libservapplib.a: sources/main/CMakeFiles/servapplib.dir/event_loop.c.o
sources/main/libservapplib.a: sources/main/CMakeFiles/servapplib.dir/misc.c.o
sources/main/libservapplib.a: sources/main/CMakeFiles/servapplib.dir/setup.c.o
sources/main/libservapplib.a: sources/main/CMakeFiles/servapplib.dir/connection_handlers.c.o
sources/main/libservapplib.a: sources/main/CMakeFiles/servapplib.dir/build.make
sources/main/libservapplib.a: sources/main/CMakeFiles/servapplib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ker0/test/C_lang/http_server_iouring/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C static library libservapplib.a"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && $(CMAKE_COMMAND) -P CMakeFiles/servapplib.dir/cmake_clean_target.cmake
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/servapplib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sources/main/CMakeFiles/servapplib.dir/build: sources/main/libservapplib.a
.PHONY : sources/main/CMakeFiles/servapplib.dir/build

sources/main/CMakeFiles/servapplib.dir/clean:
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && $(CMAKE_COMMAND) -P CMakeFiles/servapplib.dir/cmake_clean.cmake
.PHONY : sources/main/CMakeFiles/servapplib.dir/clean

sources/main/CMakeFiles/servapplib.dir/depend:
	cd /home/ker0/test/C_lang/http_server_iouring/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ker0/test/C_lang/http_server_iouring /home/ker0/test/C_lang/http_server_iouring/sources/main /home/ker0/test/C_lang/http_server_iouring/build /home/ker0/test/C_lang/http_server_iouring/build/sources/main /home/ker0/test/C_lang/http_server_iouring/build/sources/main/CMakeFiles/servapplib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sources/main/CMakeFiles/servapplib.dir/depend

