//
//

#include "../../include/commands/delete_logical_volume_command.hpp"

namespace gorynych {
    namespace workers {

        DeleteLogicalVolumeWorkerCommand::DeleteLogicalVolumeWorkerCommand(const std::string volume_group_name,
                                                         const std::string logical_volume_name)
                : AbstractWorkerCommand(WorkerCommandType::DELETE_LOGICAL_VOLUME), volumeGroupName_(volume_group_name),
                  logicalVolumeName_(logical_volume_name) {}

        const std::string & gorynych::workers::DeleteLogicalVolumeWorkerCommand::logicalVolumeName() const {
            return logicalVolumeName_;
        }

        const std::string &gorynych::workers::DeleteLogicalVolumeWorkerCommand::volumeGroupName() const {
            return volumeGroupName_;
        }
    }
}