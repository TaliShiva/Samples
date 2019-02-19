cmake_minimum_required(VERSION 3.5)
project(single_controller_storage_system)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O0 -pedantic-errors -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Wno-ignored-qualifiers -Wno-unused-parameter")


########################################### Здесь подключаем разные зависимости
####Подключаем Google Protobuf
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
#Список файлов *.proto для компиляции
set (ProtobufTestsProtoSources "${PROJECT_SOURCE_DIR}/transport/src/proto/command_api.proto")
#Запускаем компиляцию файлов .proto в C++ код
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${ProtobufTestsProtoSources})
####Закончили подключать Google Protobuf

####Подключаем Boost
find_package(Boost 1.58.0 COMPONENTS system date_time filesystem thread regex serialization)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()
include_directories(${BOOST_INCLUDE_DIRS})
####Закончили подключать Boost
#### Подключаем Qt
#set(QT_PATH "/opt/qt/5.7/gcc_64/")
#указать путь к  Qt на своей машине
#set(CMAKE_PREFIX_PATH ${QT_PATH})
#set(CMAKE_AUTOMOC ON)#Q_OBJECT - для использования в проекте механизма сигналов и слотов.
#find_package(Qt5Core REQUIRED)# по аналогии с *.pro QT += gui core
#include_directories(${Qt5Core_INCLUDE_DIRS})
# Подключаем Threads
find_package(Threads)
########################################### Здесь подключаем наши модули
###################### Модуль transport
# Список *.cpp которые нужно скомпилировать для использования модуля transport сохраняем в переменную TRANSPORT_SOURCE_FILES
set(TRANSPORT_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/transport/src/command/open.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/open.hpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/close.hpp
        ${PROJECT_SOURCE_DIR}/transport/include/response/text.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/close.cpp
        ${PROJECT_SOURCE_DIR}/transport/src/response/text.cpp
        ${PROJECT_SOURCE_DIR}/transport/src/network.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/network.hpp
        ${PROJECT_SOURCE_DIR}/transport/include/packet.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/packet.cpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/create_iscsi_target_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/create_iscsi_target_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/abstract_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/abstract_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/include/command.hpp
        ${PROJECT_SOURCE_DIR}/transport/include/response.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/connect_device_to_iscsi_target_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/connect_device_to_iscsi_target_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/connect_device_to_iscsi_target_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/connect_device_to_iscsi_target_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/create_raid_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/create_raid_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/destroy_raid_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/destroy_raid_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/add_disk_to_scst_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/add_disk_to_scst_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/remove_iscsi_target_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/remove_iscsi_target_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/remove_disk_from_scst_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/remove_disk_from_scst_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/remove_iscsi_target_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/remove_iscsi_target_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/create_lvm_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/create_lvm_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/create_logical_volume_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/create_logical_volume_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/include/transport_api.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/destroy_lvm_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/destroy_lvm_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/delete_logical_volume_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/delete_logical_volume_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/disable_iscsi_target_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/disable_iscsi_target_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/disconnect_device_to_iscsi_target_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/disconnect_device_to_iscsi_target_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/list/list_raid_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/list/list_raid_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/list/list_logical_volume_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/list/list_logical_volume_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/list/list_scst_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/list/list_scst_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/response/list_raid_response.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/response/list_raid_response.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/response/abstract_response.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/response/abstract_response.hpp
        ${PROJECT_SOURCE_DIR}/transport/include/struct/list/state_items.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/response/list_logical_volume_response.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/response/list_logical_volume_response.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/response/list_scst_response.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/response/list_scst_response.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/create_cached_disk_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/create_cached_disk_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/enable_iscsi_target_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/enable_iscsi_target_command.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/detach_cached_disk_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/detach_cached_disk_command.hpp
        )

set(TRANSPORT_CLIENT_SOURCE_FILES
        ${TRANSPORT_SOURCE_FILES}
        ${PROJECT_SOURCE_DIR}/transport/src/client.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/client.hpp
        ${PROJECT_SOURCE_DIR}/transport/src/command/disconnect_device_to_iscsi_target_command.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/command/disconnect_device_to_iscsi_target_command.hpp)

set(TRANSPORT_SERVER_SOURCE_FILES
        ${TRANSPORT_SOURCE_FILES}
        ${PROJECT_SOURCE_DIR}/transport/src/server.cpp
        ${PROJECT_SOURCE_DIR}/transport/include/server.hpp
        )
set(LOGIC_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/logic_module/src/logic_module.cpp
        ${PROJECT_SOURCE_DIR}/logic_module/include/logic_module.hpp
        ${PROJECT_SOURCE_DIR}/logic_module/src/state/system_state.cpp
        ${PROJECT_SOURCE_DIR}/logic_module/include/state/system_state.hpp)

set(WORKERS_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/worker_manager/src/worker_manager.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/worker_manager.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/worker_thread.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/worker_thread.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/open_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/open_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/close_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/close_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/include/abstract_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/open_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/open_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/close_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/close_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/iworker_response.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/abstract_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/abstract_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/create_target_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/create_target_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/iworker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/iworker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/abstract_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/abstract_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/create_target_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/create_target_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/scst/abstract_scst_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/scst/abstract_scst_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/scst/create_iscsi_target_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/scst/create_iscsi_target_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/abstract_worker_old.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/abstract_worker_old.hpp
        ${PROJECT_SOURCE_DIR}/workers/include/bcache/create_cached_disk_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/bcache/create_cached_disk_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/bcache/detach_cached_disk_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/bcache/detach_cached_disk_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/detach_cached_disk_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/detach_cached_disk_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/create_cached_disk_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/create_cached_disk_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/scst/create_iscsi_target_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/scst/create_iscsi_target_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/abstact_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/add_disk_to_scst_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/add_disk_to_scst_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/scst/add_disk_to_scst_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/scst/add_disk_to_scst_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/add_disk_to_scst_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/add_disk_to_scst_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/abstact_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/scst/remove_iscsi_target_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/scst/remove_iscsi_target_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/remove_iscsi_target_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/remove_iscsi_target_workers_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/remove_iscsi_target_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/src/scst/remove_iscsi_target_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/scst/remove_iscsi_target_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/remove_disk_from_scst_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/remove_disk_from_scst_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/remove_disk_from_scst_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/remove_disk_from_scst_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/scst/remove_disk_from_scst_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/scst/remove_disk_from_scst_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/include/scst/remove_iscsi_target_worker.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/abstact_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/md/create_raid_worker.cpp workers/include/md/create_raid_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/create_raid_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/create_raid_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/create_raid_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/create_raid_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/md/create_raid_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/md/create_raid_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/md/destroy_raid_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/md/destroy_raid_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/destroy_raid_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/destroy_raid_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/destroy_raid_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/destroy_raid_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/md/destroy_raid_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/md/destroy_raid_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/create_raid_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/create_lvm_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/create_lvm_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/create_lvm_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/create_lvm_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/lvm/create_lvm_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/lvm/create_lvm_worker.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/lvm/create_lvm_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/lvm/create_lvm_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/md/create_raid_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/lvm/create_logical_volume_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/lvm/create_logical_volume_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/create_logical_volume_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/create_logical_volume_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/create_logical_volume_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/create_logical_volume_response.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/md/create_raid_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/lvm/destroy_lvm_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/lvm/destroy_lvm_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/destroy_lvm_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/destroy_lvm_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/destroy_lvm_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/destroy_lvm_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/lvm/destroy_lvm_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/lvm/destroy_lvm_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/lvm/delete_logical_volume_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/lvm/delete_logical_volume_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/delete_logical_volume_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/delete_logical_volume_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/delete_logical_volume_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/delete_logical_volume_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/lvm/delete_logical_volume_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/lvm/delete_logical_volume_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/disable_iscsi_target_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/disable_iscsi_target_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/disable_iscsi_target_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/scst/disable_iscsi_target_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/scst/disable_iscsi_target_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/scst/disable_iscsi_target_worker.cpp workers/include/scst/disable_iscsi_target_worker.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/abstact_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/scst/connect_device_to_iscsi_target_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/scst/connect_device_to_iscsi_target_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/connect_device_to_iscsi_target_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/scst/connect_device_to_iscsi_target_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/scst/connect_device_to_iscsi_target_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/connect_device_to_iscsi_target_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/connect_device_to_iscsi_target_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/connect_device_to_iscsi_target_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/disconnect_device_to_iscsi_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/disconnect_device_to_iscsi_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/disconnect_device_to_iscsi_target_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/disconnect_device_to_iscsi_target_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/scst/disconnect_device_to_iscsi_target_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/scst/disconnect_device_to_iscsi_target_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/remove_iscsi_target_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/scst/disconnect_device_to_iscsi_target_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/scst/disconnect_device_to_iscsi_target_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/connect_device_to_iscsi_target_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/connect_device_to_iscsi_target_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/connect_device_to_iscsi_target_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/src/scst/enable_iscsi_target_worker.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/scst/enable_iscsi_target_worker.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/commands/enable_iscsi_target_worker_command.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/commands/enable_iscsi_target_worker_command.hpp
        ${PROJECT_SOURCE_DIR}/workers/src/responses/enable_iscsi_target_worker_response.cpp
        ${PROJECT_SOURCE_DIR}/workers/include/responses/enable_iscsi_target_worker_response.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/src/factories/scst/enable_iscsi_target_worker_factory.cpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/scst/enable_iscsi_target_worker_factory.hpp
        ${PROJECT_SOURCE_DIR}/worker_manager/include/factories/scst/disconnect_device_to_iscsi_target_worker_factory.hpp
        )

set(CLI_SOURCE_FILES
        "")

set(ADMIN_MODULE_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/admin_module/src/admin_module.cpp
        ${PROJECT_SOURCE_DIR}/admin_module/include/admin_module.hpp
        )

set(UTILS_MODULE_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/utils/src/start_custom_programm.cpp
        ${PROJECT_SOURCE_DIR}/utils/include/start_custom_programm.hpp
        ${PROJECT_SOURCE_DIR}/utils/src/build__scst_vdisk_name.cpp
        ${PROJECT_SOURCE_DIR}/utils/include/build__scst_vdisk_name.hpp
        ${PROJECT_SOURCE_DIR}/utils/src/get_bcache_path.cpp
        ${PROJECT_SOURCE_DIR}/utils/include/get_bcache_path.hpp
        ${PROJECT_SOURCE_DIR}/utils/src/bcache_utils.cpp
        ${PROJECT_SOURCE_DIR}/utils/include/bcache_utils.hpp
        )

# Компилируем *.cpp для модуля transport во временные обьекты,
# после этого их можно подключать в другие цели через $<TARGET_OBJECTS:transport>
#[[add_library(transport_client OBJECT
        ${TRANSPORT_CLIENT_SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS})

add_library(transport_server OBJECT
        ${TRANSPORT_SERVER_SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS})

add_library(CLI OBJECT
        ${CLI_SOURCE_FILES})

add_library(admin_module OBJECT
        ${ADMIN_MODULE_SOURCE_FILES})

add_library(utils_module OBJECT
        ${UTILS_MODULE_SOURCE_FILES})]]

########################################### Здесь собираем бинарники для нашего проекта
# Собираем бинарник модуля администрирования
add_executable(gorynych-admin
        ${PROJECT_SOURCE_DIR}/CLI/src/main.cpp
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${CLI_SOURCE_FILES}
        ${ADMIN_MODULE_SOURCE_FILES}
        ${TRANSPORT_CLIENT_SOURCE_FILES}
        )

target_link_libraries(gorynych-admin
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES}
        )

# Собираем бинарник модуля управления
add_executable(gorynych-control
        ${PROJECT_SOURCE_DIR}/transport/src/main.cpp
        ${TRANSPORT_SERVER_SOURCE_FILES}
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${LOGIC_SOURCE_FILES}
        ${WORKERS_SOURCE_FILES}
        ${UTILS_MODULE_SOURCE_FILES}
        )

# Внешние библиотеки которые нужно прилинковать к бинарнику модуля управления
target_link_libraries(gorynych-control
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES}
        )
########################################### Здесь собираем разные бинарники для тестов

################################ google test demo ##############################################
add_subdirectory(${PROJECT_SOURCE_DIR}/test/3rd_party/googletest)#add google test directory
include_directories(${PROJECT_SOURCE_DIR}/test/3rd_party/googletest/googletest/include)

add_executable(google_test_demo
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${CLI_SOURCE_FILES}
        ${ADMIN_MODULE_SOURCE_FILES}
        ${TRANSPORT_CLIENT_SOURCE_FILES}
        ${TRANSPORT_SERVER_SOURCE_FILES}
        ${LOGIC_SOURCE_FILES}
        ${WORKERS_SOURCE_FILES}
        ${UTILS_MODULE_SOURCE_FILES}
        ${PROJECT_SOURCE_DIR}/worker_manager/test/worker_manager_gtest.cpp
        ${PROJECT_SOURCE_DIR}/transport/test/transport_gtest.cpp
        ${PROJECT_SOURCE_DIR}/workers/test/workers_gtest.cpp
        ${PROJECT_SOURCE_DIR}/logic_module/test/logic_gtest.cpp
        ${PROJECT_SOURCE_DIR}/CLI/test/cli_gtest.cpp
        ${PROJECT_SOURCE_DIR}/admin_module/test/admin_gtest.cpp)

# Внешние библиотеки которые нужно прилинковать к бинарнику
target_link_libraries(google_test_demo
        ${PROTOBUF_LIBRARY}
        ${Boost_LIBRARIES}
        gtest #непосредственно сама библиотека
        gtest_main #позволяет запускать все имеющиеся тесты одновременно, это вариант для ленивых
        )
