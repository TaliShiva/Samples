cmake_minimum_required(VERSION 3.7)
project(async_client_server_from_hubr)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES async_server.cpp async_client.cpp)

find_package(Boost COMPONENTS system date_time filesystem thread regex serialization)

add_executable(async_client async_client.cpp)

target_link_libraries (async_client ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} -lboost_system)

add_executable(async_server async_server.cpp)

target_link_libraries (async_server ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} -lboost_system)
