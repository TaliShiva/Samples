cmake_minimum_required(VERSION 3.7)
project(raods_api)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(raods_api ${SOURCE_FILES})