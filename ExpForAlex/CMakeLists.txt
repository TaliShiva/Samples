cmake_minimum_required(VERSION 3.7)
project(ExpForAlex)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(ExpForAlex ${SOURCE_FILES})
target_link_libraries (ExpForAlex ${CMAKE_THREAD_LIBS_INIT} -lpthread)