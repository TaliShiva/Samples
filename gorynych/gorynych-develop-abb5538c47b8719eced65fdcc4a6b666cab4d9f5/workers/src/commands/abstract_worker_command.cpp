#include "../../include/commands/abstract_worker_command.hpp"
namespace gorynych {
    namespace workers {
        AbstractWorkerCommand::AbstractWorkerCommand(const WorkerCommandType type)
                : type_(type) {}
    }
}

