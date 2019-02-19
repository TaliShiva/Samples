cmake_minimum_required(VERSION 3.7)
project(test_engine)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -shared -Wl,-soname,-test_cock.so -fpic -fpermissive")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -fpermissive -Wall -DFIO_EXTERNAL_ENGINE")

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ../../fio/fio/fio.h
        #cmake-build-debug/test_class.cpp c
        #make-build-debug/test_class.hpp

        #../../fio/fio
        )
#add_library(netutils STATIC IMPORTED )

add_library(test_engine SHARED main.cpp ${SOURCE_FILES})
