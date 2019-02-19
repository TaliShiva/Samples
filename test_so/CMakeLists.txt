cmake_minimum_required(VERSION 3.7)
project(test_so)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive")

set(SOURCE_FILES main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(test_so ${SOURCE_FILES})
target_link_libraries(test_so dl)