cmake_minimum_required(VERSION 3.7)
project(ctest_engine)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES library.c library.h)
add_library(ctest_engine SHARED ${SOURCE_FILES})