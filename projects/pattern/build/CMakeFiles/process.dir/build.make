# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern/build

# Include any dependencies generated for this target.
include CMakeFiles/process.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/process.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/process.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/process.dir/flags.make

CMakeFiles/process.dir/lib/Process.c.o: CMakeFiles/process.dir/flags.make
CMakeFiles/process.dir/lib/Process.c.o: ../lib/Process.c
CMakeFiles/process.dir/lib/Process.c.o: CMakeFiles/process.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/process.dir/lib/Process.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/process.dir/lib/Process.c.o -MF CMakeFiles/process.dir/lib/Process.c.o.d -o CMakeFiles/process.dir/lib/Process.c.o -c /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern/lib/Process.c

CMakeFiles/process.dir/lib/Process.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/process.dir/lib/Process.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern/lib/Process.c > CMakeFiles/process.dir/lib/Process.c.i

CMakeFiles/process.dir/lib/Process.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/process.dir/lib/Process.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern/lib/Process.c -o CMakeFiles/process.dir/lib/Process.c.s

# Object files for target process
process_OBJECTS = \
"CMakeFiles/process.dir/lib/Process.c.o"

# External object files for target process
process_EXTERNAL_OBJECTS =

libprocess.a: CMakeFiles/process.dir/lib/Process.c.o
libprocess.a: CMakeFiles/process.dir/build.make
libprocess.a: CMakeFiles/process.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libprocess.a"
	$(CMAKE_COMMAND) -P CMakeFiles/process.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/process.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/process.dir/build: libprocess.a
.PHONY : CMakeFiles/process.dir/build

CMakeFiles/process.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/process.dir/cmake_clean.cmake
.PHONY : CMakeFiles/process.dir/clean

CMakeFiles/process.dir/depend:
	cd /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern/build /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern/build /mnt/c/Users/mao0202/Documents/GitHub/clang/projects/pattern/build/CMakeFiles/process.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/process.dir/depend

