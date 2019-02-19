cmake_minimum_required(VERSION 3.7)
project(sysv_shared_memory)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(sysv_shared_memory ${SOURCE_FILES})