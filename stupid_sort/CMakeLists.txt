cmake_minimum_required(VERSION 3.7)
project(stupid_sort)

set(CMAKE_CXX_STANDARD 11  "${CMAKE_CXX_FLAGS} -g ")

set(SOURCE_FILES main.cpp)
add_library(stupid_sort SHARED ${SOURCE_FILES})