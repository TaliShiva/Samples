
#include "../../include/command/create_logical_volume_command.hpp"

namespace gorynych {
    namespace transport {
        CreateLogicalVolumeCommand::CreateLogicalVolumeCommand()
                : AbstractCommand(CommandType::CREATE_LOGICAL_VOLUME_COMMAND,
                                  protobuf::Command::COMMAND_CREATE_LOGICAL_VOLUME) {
        }

        CreateLogicalVolumeCommand::CreateLogicalVolumeCommand(protobuf::Command command)
                : AbstractCommand(command, CommandType::CREATE_LOGICAL_VOLUME_COMMAND,
                                  protobuf::Command::COMMAND_CREATE_LOGICAL_VOLUME) {

        }

        const std::string &CreateLogicalVolumeCommand::logicalVolumeName() const {
            return protobufMessage_.create_logical_volume().logical_volume_name();
        }

        void CreateLogicalVolumeCommand::setLogicalVolumeName(const std::string name) {
            protobufMessage_.mutable_create_logical_volume()->set_logical_volume_name(name);
        }

        const std::string &CreateLogicalVolumeCommand::logicalVolumeSize() const {
            return protobufMessage_.create_logical_volume().logical_volume_size();
        }

        void CreateLogicalVolumeCommand::setlogicalVolumeSize(const std::string size) {
            protobufMessage_.mutable_create_logical_volume()->set_logical_volume_size(size);
        }

        const std::string &CreateLogicalVolumeCommand::parentVolumeGroupName() const {
            return protobufMessage_.create_logical_volume().parent_volume_group_name();
        }

        void CreateLogicalVolumeCommand::setParentVolumeGroupName(const std::string volumeGroupName) {
            protobufMessage_.mutable_create_logical_volume()->set_parent_volume_group_name(volumeGroupName);
        }

    }

}
