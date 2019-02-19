//
// Created by oleg on 21.03.17.
//

#include "../../include/command/enable_iscsi_target_command.hpp"
namespace  gorynych {
    namespace transport {
        EnableIscsiTargetCommand::EnableIscsiTargetCommand()
                : AbstractCommand(CommandType::REMOVE_DISK_FROM_SCST_COMMAND,
                                  protobuf::Command::COMMAND_ENABLE_ISCSI_TARGET) {
        }

        EnableIscsiTargetCommand::EnableIscsiTargetCommand(protobuf::Command command)
                : AbstractCommand(command, CommandType::ENABLE_ISCSI_TARGET_COMMAND,
                                  protobuf::Command_Command_Type_COMMAND_ENABLE_ISCSI_TARGET) {

        }

        const std::string &EnableIscsiTargetCommand::targetName() const {
            return protobufMessage_.enable_iscsi_target().target_name();
        }

        void EnableIscsiTargetCommand::setTargetName(const std::string &targetName) {
            protobufMessage_.mutable_enable_iscsi_target()->set_target_name(targetName);
        }
    }
}
