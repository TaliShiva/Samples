cmake_minimum_required(VERSION 3.7)
project(Tests)

set(CMAKE_CXX_STANDARD 11)



set(SOURCE_FILES main.cpp ThreadSafeList.cpp ThreadSafeList.hpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/../../test/3rd_party/googletest)#add google test directory
include_directories(${PROJECT_SOURCE_DIR}/../../test/3rd_party/googletest/include)


add_executable(Tests ${SOURCE_FILES})
target_link_libraries(Tests gtest gtest_main)