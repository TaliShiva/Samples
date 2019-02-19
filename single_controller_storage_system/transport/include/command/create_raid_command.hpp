//
// Created by user on 14.03.17.
//

#pragma once

#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class CreateRaidCommand : public AbstractCommand {
        public:
            CreateRaidCommand(protobuf::Command &protobufMessage);

            CreateRaidCommand();

            void setRaidPath(const std::string path);

            const std::string &raidPath() const;

            void setRaidLevel(unsigned int level);

            const unsigned int raidLevel() const;

            void setDevicesCount(unsigned int devices_count);

            const unsigned int deviceCount() const;

            void setDevices(const std::vector<std::string> devices);

            const std::vector<std::string> devices() const;
        };
    }
}