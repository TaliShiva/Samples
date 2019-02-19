#include "../../include/command/delete_logical_volume_command.hpp"

namespace gorynych {
    namespace transport {
        DeleteLogicalVolumeCommand::DeleteLogicalVolumeCommand()
                : AbstractCommand(CommandType::DELETE_LOGICAL_VOLUME_COMMAND, protobuf::Command::COMMAND_DELETE_LOGICAL_VOLUME) {

        }

        DeleteLogicalVolumeCommand::DeleteLogicalVolumeCommand(protobuf::Command &protobufMessage_) : AbstractCommand(
                protobufMessage_, CommandType::DELETE_LOGICAL_VOLUME_COMMAND, protobuf::Command::COMMAND_DELETE_LOGICAL_VOLUME) {

        }

        const std::string DeleteLogicalVolumeCommand::volumeGroupName() const{
            return protobufMessage_.delete_logical_volume().volume_group_name();
        }

        void DeleteLogicalVolumeCommand::setVolumeGroupName(const std::string volumeGroupName) {
            protobufMessage_.mutable_delete_logical_volume()->set_volume_group_name(volumeGroupName);
        }

        void DeleteLogicalVolumeCommand::setLogicalVolumeName(const std::string name) {
                protobufMessage_.mutable_delete_logical_volume()->set_logical_volume_name(name);
        }

        const std::string DeleteLogicalVolumeCommand::logicalVolumeName() const {
            return protobufMessage_.delete_logical_volume().logical_volume_name();
        }
    }
}