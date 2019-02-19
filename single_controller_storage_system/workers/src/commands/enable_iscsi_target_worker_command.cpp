#include "../../include/commands/enable_iscsi_target_worker_command.hpp"

namespace gorynych {
    namespace workers {

        EnableIscsiTargetWorkerCommand::EnableIscsiTargetWorkerCommand(const std::string &targetName)
                : AbstractWorkerCommand(WorkerCommandType::ENABLE_ISCSI_TARGET_WORKER), targetName_(targetName) {}
    }
}


