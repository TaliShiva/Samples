//

#include "../../include/command/disable_iscsi_target_command.hpp"
namespace gorynych {
    namespace transport {
        DisableIscsiTargetCommand::DisableIscsiTargetCommand()
                : AbstractCommand(CommandType::DISABLE_ISCSI_TARGET_COMMAND,
                                  protobuf::Command::COMMAND_DISABLE_ISCSI_TARGET) {

        }

        DisableIscsiTargetCommand::DisableIscsiTargetCommand(protobuf::Command command)
                : AbstractCommand(command, CommandType::DISABLE_ISCSI_TARGET_COMMAND,
                                  protobuf::Command::COMMAND_DISABLE_ISCSI_TARGET) {
        }

        const std::string &DisableIscsiTargetCommand::targetName() const {
            return protobufMessage_.disable_iscsi_target().iscsi_target_name();
        }

        void DisableIscsiTargetCommand::setTargetName(const std::string &targetName) {
            protobufMessage_.mutable_disable_iscsi_target()->set_iscsi_target_name(targetName);
        }
    }
}
