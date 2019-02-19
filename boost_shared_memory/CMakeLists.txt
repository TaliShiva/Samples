cmake_minimum_required(VERSION 3.7)
project(boost_shared_memory)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
find_package(Boost COMPONENTS system date_time filesystem thread regex serialization )
add_executable(boost_shared_memory ${SOURCE_FILES})
target_link_libraries (boost_shared_memory ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} -lboost_system -lrt)