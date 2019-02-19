cmake_minimum_required(VERSION 3.7)
project(paralle_qsort)

set(CMAKE_CXX_STANDARD 11 )

FIND_PACKAGE (Threads)

set(SOURCE_FILES main.cpp)
add_executable(paralle_qsort ${SOURCE_FILES} )

target_link_libraries(paralle_qsort -pthread -O2)