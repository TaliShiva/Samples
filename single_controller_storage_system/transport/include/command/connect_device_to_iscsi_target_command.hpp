#pragma once

#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class ConnectDeviceToIscsiTargetCommand : public AbstractCommand {
        public:
            ConnectDeviceToIscsiTargetCommand();

            ConnectDeviceToIscsiTargetCommand(protobuf::Command command);

            const std::string targetName() const;

            void setTargetName(const std::string targetName);

            const std::string devicePath() const;

            void setDevicePath(const std::string &devicePath);

            const unsigned int lunNumber() const;

            void setLunNumber(const unsigned int lunNumber);
        private:
//            protobuf::Command &command;
        };
    }

}