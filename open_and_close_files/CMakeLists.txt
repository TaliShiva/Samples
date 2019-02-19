cmake_minimum_required(VERSION 3.7)
project(open_and_close_files)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp human.hpp)
add_executable(open_and_close_files ${SOURCE_FILES})