cmake_minimum_required(VERSION 3.5)
project(basic_element C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O0 -pedantic-errors -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Wno-ignored-qualifiers -Wno-unused-parameter")


#### Adding Google Protobuf
find_package(Protobuf REQUIRED)
#Список файлов *.proto для компиляции
set (ProtobufTestsProtoSources "${PROJECT_SOURCE_DIR}/src/statistics/report/protobuf/report.proto")
#Запускаем компиляцию файлов .proto в C++ код
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${ProtobufTestsProtoSources})

find_package(Threads)
find_package(Boost COMPONENTS system date_time filesystem thread log)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif ()
add_subdirectory(${PROJECT_SOURCE_DIR}/test/3rd_party/googletest)
include_directories(${BOOST_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/test/3rd_party/googletest/googletest/include)

set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/include/disk_performer/DiskPerformer.hpp
        ${PROJECT_SOURCE_DIR}/include/TestProgram.hpp
        ${PROJECT_SOURCE_DIR}/include/global_buffer/GlobalBufferMock.hpp
        ${PROJECT_SOURCE_DIR}/include/disk_performer/hw_queue_mirror/HWQueueMirrorBuffer.hpp
        ${PROJECT_SOURCE_DIR}/include/disk_performer/hw_queue_mirror/HWQueueMirrorElement.hpp
        ${PROJECT_SOURCE_DIR}/include/disk_performer/local_disk_queue/LocalDiskQueueElement.hpp
        ${PROJECT_SOURCE_DIR}/include/disk_performer/local_disk_queue/LocalDiskQueue.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/system/SolidDataChain.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/system/SolidData.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/system/DataAtom.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/client/ClientDataAtomWrite.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/client/ClientDataPacketWrite.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/client/ClientDataStripeWrite.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/physical/PhysicalRegion.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/RawDataWrite.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/system/ChecksumChainWrite.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/system/ChecksumSolidDataWrite.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/system/DataStripeWrite.hpp
        ${PROJECT_SOURCE_DIR}/include/data_entity/system/FullStripeWrite.hpp
        ${PROJECT_SOURCE_DIR}/include/statistics/ExternalStatistics.hpp
        ${PROJECT_SOURCE_DIR}/include/disk_performer/statistics/EntityStatisticsBuffer.hpp
        ${PROJECT_SOURCE_DIR}/include/disk_performer/statistics/EntityStatistics.hpp
        ${PROJECT_SOURCE_DIR}/include/statistics/report/IReport.hpp
        ${PROJECT_SOURCE_DIR}/include/statistics/report/ReportQueue.hpp
        ${PROJECT_SOURCE_DIR}/include/statistics/report/SensorsReport.hpp
        ${PROJECT_SOURCE_DIR}/include/statistics/report/StartReport.hpp
        ${PROJECT_SOURCE_DIR}/include/statistics/report/StopReport.hpp
        ${PROJECT_SOURCE_DIR}/include/load/LoadParameters.hpp
        ${PROJECT_SOURCE_DIR}/include/load/LoadProfile.hpp
        ${PROJECT_SOURCE_DIR}/include/load/LoadTemplate.hpp
        ${PROJECT_SOURCE_DIR}/include/disk_performer/DiskPort.hpp
        ${PROJECT_SOURCE_DIR}/include/utils/Packet.hpp

        ${PROJECT_SOURCE_DIR}/src/disk_performer/DiskPerformer.cpp
        ${PROJECT_SOURCE_DIR}/src/TestProgram.cpp
        ${PROJECT_SOURCE_DIR}/src/global_buffer/GlobalBufferMock.cpp
        ${PROJECT_SOURCE_DIR}/src/disk_performer/hw_queue_mirror/HWQueueMirrorBuffer.cpp
        ${PROJECT_SOURCE_DIR}/src/disk_performer/hw_queue_mirror/HWQueueMirrorElement.cpp
        ${PROJECT_SOURCE_DIR}/src/disk_performer/local_disk_queue/LocalDiskQueue.cpp
        ${PROJECT_SOURCE_DIR}/src/disk_performer/local_disk_queue/LocalDiskQueueElement.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/system/SolidDataChain.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/system/SolidData.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/system/DataAtom.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/client/ClientDataAtomWrite.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/client/ClientDataPacketWrite.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/client/ClientDataStripeWrite.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/physical/PhysicalRegion.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/RawDataWrite.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/system/ChecksumChainWrite.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/system/ChecksumSolidDataWrite.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/system/DataStripeWrite.cpp
        ${PROJECT_SOURCE_DIR}/src/data_entity/system/FullStripeWrite.cpp
        ${PROJECT_SOURCE_DIR}/src/statistics/ExternalStatistics.cpp
        ${PROJECT_SOURCE_DIR}/src/disk_performer/statistics/EntityStatisticsBuffer.cpp
        ${PROJECT_SOURCE_DIR}/src/disk_performer/statistics/EntityStatistics.cpp
        ${PROJECT_SOURCE_DIR}/src/statistics/report/ReportQueue.cpp
        ${PROJECT_SOURCE_DIR}/src/statistics/report/SensorsReport.cpp
        ${PROJECT_SOURCE_DIR}/src/statistics/report/StartReport.cpp
        ${PROJECT_SOURCE_DIR}/src/statistics/report/StopReport.cpp
        ${PROJECT_SOURCE_DIR}/src/disk_performer/DiskPort.cpp
        ${PROJECT_SOURCE_DIR}/src/load/LoadProfile.cpp
        ${PROJECT_SOURCE_DIR}/src/load/LoadTemplate.cpp
        ${PROJECT_SOURCE_DIR}/src/load/LoadParameters.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/Packet.cpp

        )

add_executable(basic_element main.cpp
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        )

target_link_libraries(basic_element
        aio
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )


#### Starting Google tests

add_executable(local_disk_queue_tests
        ${PROJECT_SOURCE_DIR}/test/LocalDiskQueueTest/LocalDiskQueueTest.cpp
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        )
target_link_libraries(local_disk_queue_tests gtest gtest_main
        aio
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES}
        )

add_executable(entity_statistics_buffer_tests
        test/EntityStatisticsBufferTest/EntityStatisticsBufferTest.cpp
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        )
target_link_libraries(entity_statistics_buffer_tests gtest gtest_main
        aio
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES}
        )


enable_testing()

add_executable(ExternalStatisticsTest test/ExternalStatisticsTest/ExternalStatisticsTest.cpp
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        )

target_link_libraries(ExternalStatisticsTest
        gtest gtest_main
        aio
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )

add_test(ExternalStatisticsTest ExternalStatisticsTest
        )


add_executable(hw_queue_mirror_buffer_tests
        test/HWQueueMirrorBufferTests/HWQueueMirrorBufferTests.cpp
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS})
target_link_libraries(hw_queue_mirror_buffer_tests gtest gtest_main
        aio
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES}
        )

add_executable(global_buffer_mock_tests
        test/GlobalBufferMockTests/GlobalBufferMockTests.cpp
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS})
target_link_libraries(global_buffer_mock_tests gtest gtest_main
        aio
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES})

add_executable(disk_port_tests
        test/DiskPortTest/DiskPortTests.cpp
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS})
target_link_libraries(disk_port_tests gtest gtest_main
        aio
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES})

add_executable(disk_performer_tests
        test/DiskPerformerTest/DiskPerformerTests.cpp
        ${SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS})
target_link_libraries(disk_performer_tests gtest gtest_main
        aio
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES}
        )