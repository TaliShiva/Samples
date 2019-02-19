cmake_minimum_required(VERSION 3.7)
project(BEv1_0)



find_package(Protobuf REQUIRED)
set (ProtobufTestsProtoSources "../basic_element/src/statistics/report/protobuf/report.proto")
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${ProtobufTestsProtoSources})


find_package(Threads)
find_package(Boost COMPONENTS system date_time filesystem thread log)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif ()
#add_subdirectory(../basic_element/test/3rd_party/googletest)
include_directories(${BOOST_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(../basic_element/test/3rd_party/googletest/googletest/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -o -g -fpermissive -Wall -DFIO_EXTERNAL_ENGINE ")

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        ../../fio/fio/fio.h
        ../basic_element/include/disk_performer/DiskPerformer.hpp
        ../basic_element/include/TestProgram.hpp
        ../basic_element/include/global_buffer/GlobalBufferMock.hpp
        ../basic_element/include/data_entity/RawDataWrite.hpp
        ../basic_element/include/data_entity/system/DataAtom.hpp
        ../basic_element/include/data_entity/system/SolidData.hpp
        ../basic_element/include/data_entity/system/SolidDataChain.hpp

        ../basic_element/include/disk_performer/local_disk_queue/LocalDiskQueue.hpp
        ../basic_element/include/disk_performer/local_disk_queue/LocalDiskQueueElement.hpp
        ../basic_element/include/disk_performer/hw_queue_mirror/HWQueueMirrorBuffer.hpp
        ../basic_element/include/disk_performer/hw_queue_mirror/HWQueueMirrorElement.hpp
        ../basic_element/include/disk_performer/DiskPort.hpp
        ../basic_element/include/disk_performer/statistics/EntityStatisticsBuffer.hpp
        ../basic_element/include/disk_performer/statistics/EntityStatistics.hpp

        ../basic_element/include/data_entity/client/ClientDataAtomWrite.hpp
        ../basic_element/include/data_entity/client/ClientDataPacketWrite.hpp
        ../basic_element/include/data_entity/client/ClientDataStripeWrite.hpp

        ../basic_element/include/data_entity/physical/PhysicalRegion.hpp
        ../basic_element/include/data_entity/system/ChecksumChainWrite.hpp
        ../basic_element/include/data_entity/system/ChecksumSolidDataWrite.hpp
        ../basic_element/include/data_entity/system/DataStripeWrite.hpp
        ../basic_element/include/data_entity/system/FullStripeWrite.hpp
        ../basic_element/include/statistics/ExternalStatistics.hpp

        ../basic_element/include/statistics/report/IReport.hpp
        ../basic_element/include/statistics/report/ReportQueue.hpp
        ../basic_element/include/statistics/report/SensorsReport.hpp
        ../basic_element/include/statistics/report/StartReport.hpp
        ../basic_element/include/statistics/report/StopReport.hpp
        ../basic_element/include/load/LoadParameters.hpp
        ../basic_element/include/load/LoadProfile.hpp
        ../basic_element/include/load/LoadTemplate.hpp
        ../basic_element/include/utils/Packet.hpp

        ../basic_element/src/disk_performer/DiskPerformer.cpp
        ../basic_element/src/data_entity/RawDataWrite.cpp
        ../basic_element/src/data_entity/system/DataAtom.cpp
        ../basic_element/src/data_entity/system/SolidData.cpp
        ../basic_element/src/data_entity/system/SolidDataChain.cpp

        ../basic_element/src/TestProgram.cpp
        ../basic_element/src/global_buffer/GlobalBufferMock.cpp
        ../basic_element/src/disk_performer/hw_queue_mirror/HWQueueMirrorBuffer.cpp
        ../basic_element/src/disk_performer/hw_queue_mirror/HWQueueMirrorElement.cpp
        ../basic_element/src/disk_performer/local_disk_queue/LocalDiskQueue.cpp
        ../basic_element/src/disk_performer/local_disk_queue/LocalDiskQueueElement.cpp
        ../basic_element/src/data_entity/client/ClientDataAtomWrite.cpp
        ../basic_element/src/data_entity/client/ClientDataPacketWrite.cpp
        ../basic_element/src/data_entity/client/ClientDataStripeWrite.cpp
        ../basic_element/src/data_entity/physical/PhysicalRegion.cpp
        ../basic_element/src/data_entity/system/ChecksumChainWrite.cpp
        ../basic_element/src/data_entity/system/ChecksumSolidDataWrite.cpp
        ../basic_element/src/data_entity/system/DataStripeWrite.cpp
        ../basic_element/src/data_entity/system/FullStripeWrite.cpp
        ../basic_element/src/statistics/ExternalStatistics.cpp
        ../basic_element/src/disk_performer/statistics/EntityStatisticsBuffer.cpp
        ../basic_element/src/disk_performer/statistics/EntityStatistics.cpp
        ../basic_element/src/statistics/report/ReportQueue.cpp
        ../basic_element/src/statistics/report/SensorsReport.cpp
        ../basic_element/src/statistics/report/StartReport.cpp
        ../basic_element/src/statistics/report/StopReport.cpp
        ../basic_element/src/disk_performer/DiskPort.cpp
        ../basic_element/src/load/LoadProfile.cpp
        ../basic_element/src/load/LoadTemplate.cpp
        ../basic_element/src/load/LoadParameters.cpp
        ../basic_element/src/utils/Packet.cpp

        )

add_library(BEv1_0 SHARED ${SOURCE_FILES} ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(BEv1_0
        aio
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES} -lboost_system
        ${CMAKE_THREAD_LIBS_INIT})

