
#pragma once

#include "../command.hpp"
#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        class CreateIscsiTargetCommand : public AbstractCommand {
        public:
            /**
             * @see documentation AbstractCommand
             */
            CreateIscsiTargetCommand();
            /**
             * @brief CreateIscsiTargetCommand() @see documentation AbstractCommand
             * @param command @see documentation AbstractCommand
             */
            CreateIscsiTargetCommand(protobuf::Command command);

            const std::string &targetName() const;

            void setTargetName(const std::string targetName);

        };
    }
}
