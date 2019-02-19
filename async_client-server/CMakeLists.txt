cmake_minimum_required(VERSION 3.7)
project(async_client_server)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system date_time filesystem thread regex serialization)

add_executable(async_server aserver.cpp)

target_link_libraries (async_server ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} -lboost_system)

add_executable(async_client client.cpp)

target_link_libraries (async_client ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} -lboost_system)