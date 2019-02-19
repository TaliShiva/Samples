#include "../../include/command/connect_device_to_iscsi_target_command.hpp"

namespace gorynych {
    namespace transport {
        ConnectDeviceToIscsiTargetCommand::ConnectDeviceToIscsiTargetCommand()
                : AbstractCommand(CommandType::CONNECT_DEVICE_TO_ISCSI_TARGET_COMMAND,
                                  protobuf::Command::COMMAND_CONNECT_DEVICE_TO_ISCSI_TARGET) {
        }

        ConnectDeviceToIscsiTargetCommand::ConnectDeviceToIscsiTargetCommand(protobuf::Command command)
                : AbstractCommand(command,CommandType::CONNECT_DEVICE_TO_ISCSI_TARGET_COMMAND,
                                  protobuf::Command::COMMAND_CONNECT_DEVICE_TO_ISCSI_TARGET) {
        }

        const std::string ConnectDeviceToIscsiTargetCommand::targetName() const {
            return protobufMessage_.connect_device_to_iscsi_target().target_wwn();
        }

        void ConnectDeviceToIscsiTargetCommand::setTargetName(const std::string targetName) {
            protobufMessage_.mutable_connect_device_to_iscsi_target()->set_target_wwn(targetName);
        }

        const std::string ConnectDeviceToIscsiTargetCommand::devicePath() const {
            return protobufMessage_.connect_device_to_iscsi_target().device_path();
        }

        void ConnectDeviceToIscsiTargetCommand::setDevicePath(const std::string &devicePath) {
            protobufMessage_.mutable_connect_device_to_iscsi_target()->set_device_path(devicePath);
        }

        const unsigned int ConnectDeviceToIscsiTargetCommand::lunNumber() const {
            return protobufMessage_.connect_device_to_iscsi_target().lun();
        }

        void ConnectDeviceToIscsiTargetCommand::setLunNumber(const unsigned int lunNumber) {
            protobufMessage_.mutable_connect_device_to_iscsi_target()->set_lun(lunNumber);
        }
    }
}