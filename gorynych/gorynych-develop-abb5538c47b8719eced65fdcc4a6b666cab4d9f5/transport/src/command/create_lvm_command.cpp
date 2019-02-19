
//

#include "../../include/command/create_lvm_command.hpp"

namespace gorynych {
    namespace transport {
        CreateLvmCommand::CreateLvmCommand()
                : AbstractCommand(CommandType::CREATE_LVM_COMMAND, protobuf::Command::COMMAND_CREATE_LVM) {

        }

        CreateLvmCommand::CreateLvmCommand(protobuf::Command &protobufMessage_) : AbstractCommand(
                protobufMessage_, CommandType::CREATE_LVM_COMMAND, protobuf::Command::COMMAND_CREATE_LVM) {

        }

        const std::string CreateLvmCommand::volumeGroupName() const{
            return protobufMessage_.create_lvm().volume_group_name();
        }

        void CreateLvmCommand::setVolumeGroupName(const std::string volumeGroupName) {
            protobufMessage_.mutable_create_lvm()->set_volume_group_name(volumeGroupName);
        }

        const std::string CreateLvmCommand::devicePath() const{
            return protobufMessage_.create_lvm().device_path();
        }

        void CreateLvmCommand::setDevicePath(const std::string devicePath) {
            protobufMessage_.mutable_create_lvm()->set_device_path(devicePath);
        }
    }
}