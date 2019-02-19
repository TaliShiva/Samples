//
// Created by boa on 13.03.17.
//

#include "../../include/command/remove_iscsi_target_command.hpp"

namespace gorynych {
    namespace transport {
        RemoveIscsiTargetCommand::RemoveIscsiTargetCommand() :
                AbstractCommand(CommandType::REMOVE_ISCSI_TARGET_COMMAND,
                                protobuf::Command::COMMAND_REMOVE_ISCSI_TARGET) {

        }

        RemoveIscsiTargetCommand::RemoveIscsiTargetCommand(protobuf::Command command) :
                AbstractCommand(command, CommandType::CREATE_ISCSI_TARGET_COMMAND,
                                protobuf::Command::COMMAND_REMOVE_ISCSI_TARGET) {
            targetName_ = protobufMessage_.remove_iscsi_target().target_name();

        }

        const std::string &RemoveIscsiTargetCommand::targetName() const {
            return targetName_;
        }

        void RemoveIscsiTargetCommand::setTargetName(const std::string &targetName) {
            protobufMessage_.mutable_remove_iscsi_target()->set_target_name(targetName);
        }
    }
}
