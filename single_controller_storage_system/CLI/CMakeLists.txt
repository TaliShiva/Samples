cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE_FILES
        "src/main.cpp")

add_executable(test1 ${SOURCE_FILES})

target_link_libraries(test1)



