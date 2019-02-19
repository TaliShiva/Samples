
#include "../../include/command/add_disk_to_scst_command.hpp"

namespace gorynych {
    namespace transport {

        AddDiskToScstCommand::AddDiskToScstCommand(protobuf::Command command)
                : AbstractCommand(command, CommandType::ADD_DISK_TO_SCST_COMMAND,
                                  protobuf::Command::COMMAND_ADD_DISK_TO_SCST) {

        }

        AddDiskToScstCommand::AddDiskToScstCommand()
                : AbstractCommand(CommandType::ADD_DISK_TO_SCST_COMMAND,
                                  protobuf::Command::COMMAND_ADD_DISK_TO_SCST) {

        }

        const std::string &AddDiskToScstCommand::devicePath() const {
            return protobufMessage_.add_disk_to_scst().device_path();
        }

        void AddDiskToScstCommand::setDevicePath(const std::string devicePath) {
            protobufMessage_.mutable_add_disk_to_scst()->set_device_path(devicePath);
        }

        void AddDiskToScstCommand::print() {
            std::cout << "Команда клиента adddisktoscst. " << std::endl;
            std::cout << "target_wwn: " << protobufMessage_.add_disk_to_scst().device_path() << std::endl;
        }
    }
}
