
#pragma once

#include "command/open.hpp"
#include "command/close.hpp"
#include "response/text.hpp"

#include <boost/asio.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>

#include "../include/transport_api.hpp"
#include "../include/packet.hpp"
#include "../include/network.hpp"
#include "command/create_raid_command.hpp"
#include "command/destroy_raid_command.hpp"
#include "command/remove_iscsi_target_command.hpp"
#include "command/create_cached_disk_command.hpp"
#include "command/detach_cached_disk_command.hpp"
#include "command/delete_logical_volume_command.hpp"
#include "command.hpp"

namespace gorynych {
    namespace transport {
        class Sender {
        public:
            /**
             * Класс для отправки команд через сокет
             * @param file Путь к файлу сокета
             */
            Sender(std::string file);
            /**
             * @brief Отправка команды OpenCommand
             * @param command команда
             */
            TextResponse sendCommand(OpenCommand &command);

            /**
             * @brief Отправка команды CloseCommand
             * @param command команда
             */
            TextResponse sendCommand(CloseCommand &command);

            /**
             * @brief Отправка команды CreateIscsiTargetCommand
             * @param command команда
             */
            TextResponse sendCommand(CreateIscsiTargetCommand &command);

            /**
             * @brief
             * @param command
             * @return
             */
            TextResponse sendCommand(AddDiskToScstCommand &command);
            /**
            * @brief отправка комманды RemoveIscsiTargetCommand
            * @param command
            * @return
            */
            TextResponse sendCommand(RemoveIscsiTargetCommand &command);

            TextResponse sendCommand(CreateRaidCommand &command);

            TextResponse sendCommand(RemoveDiskFromScstCommand &command);
            /**
             *
             * @brief - Отправка комманды для разрушения raid-а
             * @param  command команда
             */
            TextResponse sendCommand(DestroyRaidCommand &command);

            /**
             * @brief Отправка команды CreateLvmCommand
             * @param command команда
             */
            TextResponse sendCommand(CreateLvmCommand &command);


            TextResponse sendCommand(CreateLogicalVolumeCommand &command);


            /**
             * @brief Отправка команды DestroyLvmCommand
             * @param command команда
             */
            TextResponse sendCommand(DestroyLvmCommand &command);

            TextResponse sendCommand(CreateCachedDiskCommand &command);

            TextResponse sendCommand(DetachCachedDiskCommand &command);

            /**
             * @brief Отправка команды DeleteLogicalVolumeCommand
             * @param command команда
             */
            TextResponse sendCommand(DeleteLogicalVolumeCommand &command);

            TextResponse sendCommand(DisableIscsiTargetCommand &command);

            TextResponse sendCommand(ConnectDeviceToIscsiTargetCommand &command);

            TextResponse sendCommand(DisconnectDeviceToIscsiTargetCommand &command);


            TextResponse sendCommand(EnableIscsiTargetCommand &command);
            ListRaidResponse sendCommand(ListRaidCommand &command);

            ListLogicalVolumeResponse sendCommand(ListLogicalVolumeCommand &command);

            ListScstResponse sendCommand(ListScstCommand &command);
        private:
            std::string file_;

            std::string sendData(ICommand &command);
        };
    }
}
