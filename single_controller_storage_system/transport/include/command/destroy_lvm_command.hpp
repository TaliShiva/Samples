
#pragma once

#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class DestroyLvmCommand : public AbstractCommand {
        public:
            /**
             * @brief Создать пустую команду DestroyLvmCommand
             */
            DestroyLvmCommand();

            /**
             * @brief Создать команду DestroyLvmCommand из данных protobuf
             * @param command обьект команды Protobuf
             */
            DestroyLvmCommand(protobuf::Command &protobufMessage_);

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
             * @brief getter
             * @return Путь к устройству на котором нужно создать LVM
             */
            const std::string devicePath() const;

            /**
             * @brief setter
             * @param devicePath Путь к устройству на котором нужно создать LVM
             */
            void setDevicePath(const std::string devicePath);
        };
    }
}
