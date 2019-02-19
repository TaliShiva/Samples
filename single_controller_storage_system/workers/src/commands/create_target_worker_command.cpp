#include "../../include/commands/create_target_worker_command.hpp"

namespace gorynych {
    namespace workers {
        CreateTargetWorkerCommand::CreateTargetWorkerCommand(const std::string targetName)
                : AbstractWorkerCommand(WorkerCommandType::CREATE_TARGET), targetName_(targetName) {}

        const std::string CreateTargetWorkerCommand::targetName() const {
            return targetName_;
        }
    }
}

