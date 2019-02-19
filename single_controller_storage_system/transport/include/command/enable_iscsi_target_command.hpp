#pragma once

#include "abstract_command.hpp"
#include "../../../workers/include/commands/enable_iscsi_target_worker_command.hpp"

namespace gorynych {
    namespace transport {
        class EnableIscsiTargetCommand : public AbstractCommand {
        public:
            EnableIscsiTargetCommand();

            EnableIscsiTargetCommand(protobuf::Command command);


            const std::string &targetName() const;

            void setTargetName(const std::string &targetName);
        };
    }
}


