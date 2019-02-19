cmake_minimum_required(VERSION 3.6)
project(protobuf_example)

set(CMAKE_CXX_STANDARD 11)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
#...
set (ProtobufTestsProtoSources
    command_api.proto
)
#...
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS proto/${ProtobufTestsProtoSources})
#add_executable(ProtobufTests ${ProtobufTestsSources} ${PROTO_SRCS} ${PROTO_HDRS})

#set(BOOST_ROOT "/usr/include/boost/")
#set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
#set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
find_package(Boost COMPONENTS system date_time filesystem thread regex serialization)


set(SOURCE_FILES main.cpp)
include_directories(${BOOST_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIR})


add_executable(server
        server.cpp
        ${ProtobufTestsSources}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        packet.cpp
        )

target_link_libraries(server
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES}
        )

add_executable(client
        client.cpp
        ${ProtobufTestsSources}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        packet.cpp
        )

target_link_libraries(client
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES} -lboost_system
        )

