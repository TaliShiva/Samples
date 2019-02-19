//

#include "../../include/commands/disable_iscsi_target_worker_command.hpp"
namespace gorynych {
    namespace workers {

        DisableIscsiTargetWorkerCommand::DisableIscsiTargetWorkerCommand()
                : AbstractWorkerCommand(WorkerCommandType::DISABLE_ISCSI_TARGET_WORKER) {
        }

        DisableIscsiTargetWorkerCommand::DisableIscsiTargetWorkerCommand(const std::string &targetName)
                : AbstractWorkerCommand(WorkerCommandType::DISABLE_ISCSI_TARGET_WORKER), targetName_(targetName){

        }
    }
}
