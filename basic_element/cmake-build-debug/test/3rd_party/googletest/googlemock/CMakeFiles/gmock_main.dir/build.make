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
CMAKE_SOURCE_DIR = /home/user/CLionProjects/basic_element

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/CLionProjects/basic_element/cmake-build-debug

# Include any dependencies generated for this target.
include test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/depend.make

# Include the progress variables for this target.
include test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/progress.make

# Include the compile flags for this target's objects.
include test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/flags.make

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/flags.make
test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o: ../test/3rd_party/googletest/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/CLionProjects/basic_element/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o"
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o -c /home/user/CLionProjects/basic_element/test/3rd_party/googletest/googletest/src/gtest-all.cc

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.i"
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/CLionProjects/basic_element/test/3rd_party/googletest/googletest/src/gtest-all.cc > CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.i

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.s"
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/CLionProjects/basic_element/test/3rd_party/googletest/googletest/src/gtest-all.cc -o CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.s

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.requires:

.PHONY : test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.requires

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.provides: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.requires
	$(MAKE) -f test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/build.make test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.provides.build
.PHONY : test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.provides

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.provides.build: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o


test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/flags.make
test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o: ../test/3rd_party/googletest/googlemock/src/gmock-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/CLionProjects/basic_element/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o"
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/src/gmock-all.cc.o -c /home/user/CLionProjects/basic_element/test/3rd_party/googletest/googlemock/src/gmock-all.cc

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/src/gmock-all.cc.i"
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/CLionProjects/basic_element/test/3rd_party/googletest/googlemock/src/gmock-all.cc > CMakeFiles/gmock_main.dir/src/gmock-all.cc.i

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/src/gmock-all.cc.s"
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/CLionProjects/basic_element/test/3rd_party/googletest/googlemock/src/gmock-all.cc -o CMakeFiles/gmock_main.dir/src/gmock-all.cc.s

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires:

.PHONY : test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires
	$(MAKE) -f test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/build.make test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides.build
.PHONY : test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides.build: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o


test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/flags.make
test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o: ../test/3rd_party/googletest/googlemock/src/gmock_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/CLionProjects/basic_element/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o"
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.o -c /home/user/CLionProjects/basic_element/test/3rd_party/googletest/googlemock/src/gmock_main.cc

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/src/gmock_main.cc.i"
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/CLionProjects/basic_element/test/3rd_party/googletest/googlemock/src/gmock_main.cc > CMakeFiles/gmock_main.dir/src/gmock_main.cc.i

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/src/gmock_main.cc.s"
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/CLionProjects/basic_element/test/3rd_party/googletest/googlemock/src/gmock_main.cc -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.s

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires:

.PHONY : test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires
	$(MAKE) -f test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/build.make test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides.build
.PHONY : test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides.build: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o


# Object files for target gmock_main
gmock_main_OBJECTS = \
"CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o" \
"CMakeFiles/gmock_main.dir/src/gmock-all.cc.o" \
"CMakeFiles/gmock_main.dir/src/gmock_main.cc.o"

# External object files for target gmock_main
gmock_main_EXTERNAL_OBJECTS =

test/3rd_party/googletest/googlemock/libgmock_main.a: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o
test/3rd_party/googletest/googlemock/libgmock_main.a: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o
test/3rd_party/googletest/googlemock/libgmock_main.a: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
test/3rd_party/googletest/googlemock/libgmock_main.a: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/build.make
test/3rd_party/googletest/googlemock/libgmock_main.a: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/CLionProjects/basic_element/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libgmock_main.a"
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock_main.dir/cmake_clean_target.cmake
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gmock_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/build: test/3rd_party/googletest/googlemock/libgmock_main.a

.PHONY : test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/build

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/requires: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/__/googletest/src/gtest-all.cc.o.requires
test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/requires: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires
test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/requires: test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires

.PHONY : test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/requires

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/clean:
	cd /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock_main.dir/cmake_clean.cmake
.PHONY : test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/clean

test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/depend:
	cd /home/user/CLionProjects/basic_element/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/CLionProjects/basic_element /home/user/CLionProjects/basic_element/test/3rd_party/googletest/googlemock /home/user/CLionProjects/basic_element/cmake-build-debug /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock /home/user/CLionProjects/basic_element/cmake-build-debug/test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/3rd_party/googletest/googlemock/CMakeFiles/gmock_main.dir/depend
