//

#include "../../include/command/remove_disk_from_scst_command.hpp"
namespace gorynych {
    namespace transport {

        RemoveDiskFromScstCommand::RemoveDiskFromScstCommand()
                : AbstractCommand(CommandType::REMOVE_DISK_FROM_SCST_COMMAND,
                                  protobuf::Command::COMMAND_REMOVE_DISK_FROM_SCST) {

        }

        RemoveDiskFromScstCommand::RemoveDiskFromScstCommand(protobuf::Command command)
                : AbstractCommand(command, CommandType::REMOVE_DISK_FROM_SCST_COMMAND,
                                  protobuf::Command_Command_Type_COMMAND_REMOVE_DISK_FROM_SCST) {

        }

        void RemoveDiskFromScstCommand::setDevicePath(const std::string &devicePath) {
            protobufMessage_.mutable_remove_disk_from_scst()->set_device_path(devicePath);
        }

        const std::string &RemoveDiskFromScstCommand::devicePath() const {
            return protobufMessage_.remove_disk_from_scst().device_path();
        }
    }
}
