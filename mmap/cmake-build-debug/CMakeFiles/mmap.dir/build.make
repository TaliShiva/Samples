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
CMAKE_SOURCE_DIR = /home/user/CLionProjects/mmap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/CLionProjects/mmap/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mmap.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mmap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mmap.dir/flags.make

CMakeFiles/mmap.dir/main.cpp.o: CMakeFiles/mmap.dir/flags.make
CMakeFiles/mmap.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/CLionProjects/mmap/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mmap.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mmap.dir/main.cpp.o -c /home/user/CLionProjects/mmap/main.cpp

CMakeFiles/mmap.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmap.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/CLionProjects/mmap/main.cpp > CMakeFiles/mmap.dir/main.cpp.i

CMakeFiles/mmap.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmap.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/CLionProjects/mmap/main.cpp -o CMakeFiles/mmap.dir/main.cpp.s

CMakeFiles/mmap.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/mmap.dir/main.cpp.o.requires

CMakeFiles/mmap.dir/main.cpp.o.provides: CMakeFiles/mmap.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmap.dir/build.make CMakeFiles/mmap.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mmap.dir/main.cpp.o.provides

CMakeFiles/mmap.dir/main.cpp.o.provides.build: CMakeFiles/mmap.dir/main.cpp.o


# Object files for target mmap
mmap_OBJECTS = \
"CMakeFiles/mmap.dir/main.cpp.o"

# External object files for target mmap
mmap_EXTERNAL_OBJECTS =

mmap: CMakeFiles/mmap.dir/main.cpp.o
mmap: CMakeFiles/mmap.dir/build.make
mmap: CMakeFiles/mmap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/CLionProjects/mmap/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mmap"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mmap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mmap.dir/build: mmap

.PHONY : CMakeFiles/mmap.dir/build

CMakeFiles/mmap.dir/requires: CMakeFiles/mmap.dir/main.cpp.o.requires

.PHONY : CMakeFiles/mmap.dir/requires

CMakeFiles/mmap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mmap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mmap.dir/clean

CMakeFiles/mmap.dir/depend:
	cd /home/user/CLionProjects/mmap/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/CLionProjects/mmap /home/user/CLionProjects/mmap /home/user/CLionProjects/mmap/cmake-build-debug /home/user/CLionProjects/mmap/cmake-build-debug /home/user/CLionProjects/mmap/cmake-build-debug/CMakeFiles/mmap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mmap.dir/depend

