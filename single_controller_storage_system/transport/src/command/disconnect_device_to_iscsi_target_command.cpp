#include "../../include/command/disconnect_device_to_iscsi_target_command.hpp"


namespace gorynych {
    namespace transport {
        DisconnectDeviceToIscsiTargetCommand::DisconnectDeviceToIscsiTargetCommand(protobuf::Command &command)
                : AbstractCommand(command,
                                  CommandType::DISCONNECT_DEVICE_TO_ISCSI_TARGET_COMMAND,
                                  protobuf::Command::COMMAND_DISCONNECT_DEVICE_TO_ISCSI_TARGET) {

        }
        
        DisconnectDeviceToIscsiTargetCommand::DisconnectDeviceToIscsiTargetCommand()
                : AbstractCommand( CommandType::DISCONNECT_DEVICE_TO_ISCSI_TARGET_COMMAND,
                                  protobuf::Command::COMMAND_DISCONNECT_DEVICE_TO_ISCSI_TARGET) {
        }

        const std::string DisconnectDeviceToIscsiTargetCommand::targetName() const {
            return protobufMessage_.disconnect_device_to_iscsi_target().target_wwn();
        }

        void DisconnectDeviceToIscsiTargetCommand::setTargetName(const std::string targetName) {
            protobufMessage_.mutable_disconnect_device_to_iscsi_target()->set_target_wwn(targetName);

        }

        const std::string DisconnectDeviceToIscsiTargetCommand::devicePath() const {
            return protobufMessage_.disconnect_device_to_iscsi_target().device_path();
        }

        void DisconnectDeviceToIscsiTargetCommand::setDevicePath(const std::string devicePath) {
            return protobufMessage_.mutable_disconnect_device_to_iscsi_target()->set_device_path(devicePath);
        }

        const unsigned int DisconnectDeviceToIscsiTargetCommand::lunNumber() const {
            return protobufMessage_.disconnect_device_to_iscsi_target().lun();
        }

        void DisconnectDeviceToIscsiTargetCommand::setLunNumber(const unsigned int lunNumber) {
            return protobufMessage_.mutable_disconnect_device_to_iscsi_target()->set_lun(lunNumber);
        }


    }
}

