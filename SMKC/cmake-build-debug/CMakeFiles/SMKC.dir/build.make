# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/new_clion/clion-2017.1.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/new_clion/clion-2017.1.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/CLionProjects/SMKC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/CLionProjects/SMKC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SMKC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SMKC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SMKC.dir/flags.make

CMakeFiles/SMKC.dir/main.c.o: CMakeFiles/SMKC.dir/flags.make
CMakeFiles/SMKC.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/CLionProjects/SMKC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SMKC.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SMKC.dir/main.c.o   -c /home/user/CLionProjects/SMKC/main.c

CMakeFiles/SMKC.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SMKC.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/CLionProjects/SMKC/main.c > CMakeFiles/SMKC.dir/main.c.i

CMakeFiles/SMKC.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SMKC.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/CLionProjects/SMKC/main.c -o CMakeFiles/SMKC.dir/main.c.s

CMakeFiles/SMKC.dir/main.c.o.requires:

.PHONY : CMakeFiles/SMKC.dir/main.c.o.requires

CMakeFiles/SMKC.dir/main.c.o.provides: CMakeFiles/SMKC.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/SMKC.dir/build.make CMakeFiles/SMKC.dir/main.c.o.provides.build
.PHONY : CMakeFiles/SMKC.dir/main.c.o.provides

CMakeFiles/SMKC.dir/main.c.o.provides.build: CMakeFiles/SMKC.dir/main.c.o


# Object files for target SMKC
SMKC_OBJECTS = \
"CMakeFiles/SMKC.dir/main.c.o"

# External object files for target SMKC
SMKC_EXTERNAL_OBJECTS =

SMKC: CMakeFiles/SMKC.dir/main.c.o
SMKC: CMakeFiles/SMKC.dir/build.make
SMKC: CMakeFiles/SMKC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/CLionProjects/SMKC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable SMKC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SMKC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SMKC.dir/build: SMKC

.PHONY : CMakeFiles/SMKC.dir/build

CMakeFiles/SMKC.dir/requires: CMakeFiles/SMKC.dir/main.c.o.requires

.PHONY : CMakeFiles/SMKC.dir/requires

CMakeFiles/SMKC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SMKC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SMKC.dir/clean

CMakeFiles/SMKC.dir/depend:
	cd /home/user/CLionProjects/SMKC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/CLionProjects/SMKC /home/user/CLionProjects/SMKC /home/user/CLionProjects/SMKC/cmake-build-debug /home/user/CLionProjects/SMKC/cmake-build-debug /home/user/CLionProjects/SMKC/cmake-build-debug/CMakeFiles/SMKC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SMKC.dir/depend

