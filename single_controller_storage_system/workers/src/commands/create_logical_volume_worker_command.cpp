
#include "../../include/commands/create_logical_volume_worker_command.hpp"

namespace gorynych {
    namespace workers {

        CreateLogicalVolumeWorkerCommand::CreateLogicalVolumeWorkerCommand(const std::string logicalVolumeName_,
                                                                           const std::string logicalVolumeSize_,
                                                                           const std::string parentVolumeGroupName_)
                : AbstractWorkerCommand(WorkerCommandType::CREATE_LOGICAL_VOLUME),
                  logicalVolumeName_(logicalVolumeName_),
                  logicalVolumeSize_(logicalVolumeSize_), parentVolumeGroupName_(parentVolumeGroupName_) {

        }

        const std::string &CreateLogicalVolumeWorkerCommand::logicalVolumeName() const {
            return logicalVolumeName_;
        }

        const std::string &CreateLogicalVolumeWorkerCommand::logicalVolumeSize() const {
            return logicalVolumeSize_;
        }

        const std::string &CreateLogicalVolumeWorkerCommand::parentVolumeGroupName() const {
            return parentVolumeGroupName_;
        }
    }
}