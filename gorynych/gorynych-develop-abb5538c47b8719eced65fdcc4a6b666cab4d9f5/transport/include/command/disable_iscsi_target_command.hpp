#pragma once

#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class DisableIscsiTargetCommand : public AbstractCommand {
        public:
            DisableIscsiTargetCommand();

            DisableIscsiTargetCommand(protobuf::Command command);

            const std::string &targetName() const;

            void setTargetName(const std::string &targetName);
        };
    }
}




