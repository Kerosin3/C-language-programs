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
include sources/main/CMakeFiles/app.out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include sources/main/CMakeFiles/app.out.dir/compiler_depend.make

# Include the progress variables for this target.
include sources/main/CMakeFiles/app.out.dir/progress.make

# Include the compile flags for this target's objects.
include sources/main/CMakeFiles/app.out.dir/flags.make

sources/main/CMakeFiles/app.out.dir/main.c.o: sources/main/CMakeFiles/app.out.dir/flags.make
sources/main/CMakeFiles/app.out.dir/main.c.o: /home/ker0/test/C_lang/http_server_iouring/sources/main/main.c
sources/main/CMakeFiles/app.out.dir/main.c.o: sources/main/CMakeFiles/app.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ker0/test/C_lang/http_server_iouring/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object sources/main/CMakeFiles/app.out.dir/main.c.o"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT sources/main/CMakeFiles/app.out.dir/main.c.o -MF CMakeFiles/app.out.dir/main.c.o.d -o CMakeFiles/app.out.dir/main.c.o -c /home/ker0/test/C_lang/http_server_iouring/sources/main/main.c

sources/main/CMakeFiles/app.out.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.out.dir/main.c.i"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ker0/test/C_lang/http_server_iouring/sources/main/main.c > CMakeFiles/app.out.dir/main.c.i

sources/main/CMakeFiles/app.out.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.out.dir/main.c.s"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ker0/test/C_lang/http_server_iouring/sources/main/main.c -o CMakeFiles/app.out.dir/main.c.s

# Object files for target app.out
app_out_OBJECTS = \
"CMakeFiles/app.out.dir/main.c.o"

# External object files for target app.out
app_out_EXTERNAL_OBJECTS =

app.out: sources/main/CMakeFiles/app.out.dir/main.c.o
app.out: sources/main/CMakeFiles/app.out.dir/build.make
app.out: sources/contrib/libpicohttpparserlib.a
app.out: sources/main/libservapplib.a
app.out: sources/contrib/libpicohttpparserlib.a
app.out: sources/main/CMakeFiles/app.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ker0/test/C_lang/http_server_iouring/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../app.out"
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sources/main/CMakeFiles/app.out.dir/build: app.out
.PHONY : sources/main/CMakeFiles/app.out.dir/build

sources/main/CMakeFiles/app.out.dir/clean:
	cd /home/ker0/test/C_lang/http_server_iouring/build/sources/main && $(CMAKE_COMMAND) -P CMakeFiles/app.out.dir/cmake_clean.cmake
.PHONY : sources/main/CMakeFiles/app.out.dir/clean

sources/main/CMakeFiles/app.out.dir/depend:
	cd /home/ker0/test/C_lang/http_server_iouring/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ker0/test/C_lang/http_server_iouring /home/ker0/test/C_lang/http_server_iouring/sources/main /home/ker0/test/C_lang/http_server_iouring/build /home/ker0/test/C_lang/http_server_iouring/build/sources/main /home/ker0/test/C_lang/http_server_iouring/build/sources/main/CMakeFiles/app.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sources/main/CMakeFiles/app.out.dir/depend

