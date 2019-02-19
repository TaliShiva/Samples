#pragma once

#include <string>
#include "../../cmake-build-debug/command_api.pb.h"

namespace gorynych {
    namespace transport {
        /**
         * Перечисление все типов комманд
         */
        enum class CommandType{
            OPEN_COMMAND,
            CLOSE_COMMAND,
            ADD_DISK_TO_SCST_COMMAND,
            CREATE_ISCSI_TARGET_COMMAND,
            CREATE_CACHED_DISK_COMMAND,
            DETACH_CACHED_DISK_COMMAND,
            DISCONNECT_DEVICE_TO_ISCSI_TARGET_COMMAND,
            CONNECT_DEVICE_TO_ISCSI_TARGET_COMMAND,
            CREATE_RAID_COMMAND,
            DESTROY_RAID_COMMAND,
            REMOVE_ISCSI_TARGET_COMMAND,
            CREATE_LVM_COMMAND,
            REMOVE_DISK_FROM_SCST_COMMAND,
            CREATE_LOGICAL_VOLUME_COMMAND,
            DELETE_LOGICAL_VOLUME_COMMAND,
            ENABLE_ISCSI_TARGET_COMMAND,
            DISABLE_ISCSI_TARGET_COMMAND,
            DESTROY_LVM_COMMAND,
            LIST_RAID_COMMAND,
            LIST_LOGICAL_VOLUME_COMMAND,
            LIST_SCST_COMMAND,
        };

        /**
         * Общий интерфейс для всех команд
         */
        class ICommand {
        public:

/**
             * @brief Возвращает название типа команды
             * @return название тпа команды
             */
            virtual CommandType getCommandType() const =0;

            virtual std::string getCodedData() const =0;

            /**
             * @brief Проверяет что все поля, необходимые для выполнения команды заполнены
             * @return статус инициализации
             */
            virtual bool isInitializedCorrect() const =0;
        };
    }
}