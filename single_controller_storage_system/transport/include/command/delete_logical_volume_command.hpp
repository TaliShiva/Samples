
#pragma once

#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class DeleteLogicalVolumeCommand : public AbstractCommand {
        public:
            /**
             * @brief Создать пустую команду DeleteLvmCommand
             */
            DeleteLogicalVolumeCommand();

            /**
             * @brief Создать команду CreateLvmCommand из данных protobuf
             * @param command обьект команды Protobuf
             */
            DeleteLogicalVolumeCommand(protobuf::Command &protobufMessage_);

            /**
             * @brief getter
             * @return Название LVM Volume Group
             */
            const std::string volumeGroupName() const;

            /**
             * @brief setter
             * @param volumeGroupName Название LVM Volume Group
             */
            void setVolumeGroupName(const std::string volumeGroupName);
            /**
             * @param name - название удаляемых логических томов
             */
            void setLogicalVolumeName(const std::string name);
            const std::string logicalVolumeName() const;
        };
    }
}



