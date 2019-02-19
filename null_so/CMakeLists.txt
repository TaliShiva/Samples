cmake_minimum_required(VERSION 3.7)
project(test_engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fpermissive -Wall -DFIO_EXTERNAL_ENGINE")

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ../../fio/fio/fio.h)

add_library(test_engine SHARED main.cpp ${SOURCE_FILES})
