#include "../../include/command/create_iscsi_target_command.hpp"

namespace gorynych {
    namespace transport {
        CreateIscsiTargetCommand::CreateIscsiTargetCommand()
                : AbstractCommand(CommandType::CREATE_ISCSI_TARGET_COMMAND,
                                  protobuf::Command::COMMAND_CREATE_ISCSI_TARGET) {
        }

        CreateIscsiTargetCommand::CreateIscsiTargetCommand(protobuf::Command command)
                : AbstractCommand(command, CommandType::CREATE_ISCSI_TARGET_COMMAND,
                                  protobuf::Command::COMMAND_CREATE_ISCSI_TARGET) {

        }

        void CreateIscsiTargetCommand::setTargetName(const std::string targetName) {
            protobufMessage_.mutable_create_iscsi_target()->set_target_name(targetName);
        }

        const std::string &CreateIscsiTargetCommand::targetName() const {
            return protobufMessage_.create_iscsi_target().target_name();
        }
    }
}

