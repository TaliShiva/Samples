
#include "../../include/command/destroy_lvm_command.hpp"


namespace gorynych {
    namespace transport {
        DestroyLvmCommand::DestroyLvmCommand()
                : AbstractCommand(CommandType::DESTROY_LVM_COMMAND, protobuf::Command::COMMAND_DESTROY_LVM) {

        }

        DestroyLvmCommand::DestroyLvmCommand(protobuf::Command &protobufMessage_) : AbstractCommand(
                protobufMessage_, CommandType::DESTROY_LVM_COMMAND, protobuf::Command::COMMAND_DESTROY_LVM) {

        }

        const std::string DestroyLvmCommand::volumeGroupName() const{
            return protobufMessage_.destroy_lvm().volume_group_name();
        }

        void DestroyLvmCommand::setVolumeGroupName(const std::string volumeGroupName) {
            protobufMessage_.mutable_destroy_lvm()->set_volume_group_name(volumeGroupName);
        }

        const std::string DestroyLvmCommand::devicePath() const{
            return protobufMessage_.destroy_lvm().device_path();
        }

        void DestroyLvmCommand::setDevicePath(const std::string devicePath) {
            protobufMessage_.mutable_destroy_lvm()->set_device_path(devicePath);
        }
    }
}