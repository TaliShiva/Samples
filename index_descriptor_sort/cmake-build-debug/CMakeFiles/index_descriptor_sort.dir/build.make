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
CMAKE_SOURCE_DIR = /home/user/CLionProjects/index_descriptor_sort

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/CLionProjects/index_descriptor_sort/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/index_descriptor_sort.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/index_descriptor_sort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/index_descriptor_sort.dir/flags.make

CMakeFiles/index_descriptor_sort.dir/main.cpp.o: CMakeFiles/index_descriptor_sort.dir/flags.make
CMakeFiles/index_descriptor_sort.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/CLionProjects/index_descriptor_sort/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/index_descriptor_sort.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/index_descriptor_sort.dir/main.cpp.o -c /home/user/CLionProjects/index_descriptor_sort/main.cpp

CMakeFiles/index_descriptor_sort.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index_descriptor_sort.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/CLionProjects/index_descriptor_sort/main.cpp > CMakeFiles/index_descriptor_sort.dir/main.cpp.i

CMakeFiles/index_descriptor_sort.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index_descriptor_sort.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/CLionProjects/index_descriptor_sort/main.cpp -o CMakeFiles/index_descriptor_sort.dir/main.cpp.s

CMakeFiles/index_descriptor_sort.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/index_descriptor_sort.dir/main.cpp.o.requires

CMakeFiles/index_descriptor_sort.dir/main.cpp.o.provides: CMakeFiles/index_descriptor_sort.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/index_descriptor_sort.dir/build.make CMakeFiles/index_descriptor_sort.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/index_descriptor_sort.dir/main.cpp.o.provides

CMakeFiles/index_descriptor_sort.dir/main.cpp.o.provides.build: CMakeFiles/index_descriptor_sort.dir/main.cpp.o


# Object files for target index_descriptor_sort
index_descriptor_sort_OBJECTS = \
"CMakeFiles/index_descriptor_sort.dir/main.cpp.o"

# External object files for target index_descriptor_sort
index_descriptor_sort_EXTERNAL_OBJECTS =

index_descriptor_sort: CMakeFiles/index_descriptor_sort.dir/main.cpp.o
index_descriptor_sort: CMakeFiles/index_descriptor_sort.dir/build.make
index_descriptor_sort: CMakeFiles/index_descriptor_sort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/CLionProjects/index_descriptor_sort/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable index_descriptor_sort"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/index_descriptor_sort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/index_descriptor_sort.dir/build: index_descriptor_sort

.PHONY : CMakeFiles/index_descriptor_sort.dir/build

CMakeFiles/index_descriptor_sort.dir/requires: CMakeFiles/index_descriptor_sort.dir/main.cpp.o.requires

.PHONY : CMakeFiles/index_descriptor_sort.dir/requires

CMakeFiles/index_descriptor_sort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/index_descriptor_sort.dir/cmake_clean.cmake
.PHONY : CMakeFiles/index_descriptor_sort.dir/clean

CMakeFiles/index_descriptor_sort.dir/depend:
	cd /home/user/CLionProjects/index_descriptor_sort/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/CLionProjects/index_descriptor_sort /home/user/CLionProjects/index_descriptor_sort /home/user/CLionProjects/index_descriptor_sort/cmake-build-debug /home/user/CLionProjects/index_descriptor_sort/cmake-build-debug /home/user/CLionProjects/index_descriptor_sort/cmake-build-debug/CMakeFiles/index_descriptor_sort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/index_descriptor_sort.dir/depend

