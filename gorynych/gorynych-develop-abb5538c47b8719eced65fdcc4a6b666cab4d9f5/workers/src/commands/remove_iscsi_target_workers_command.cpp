//
// Created by boa on 13.03.17.
//

#include "../../include/commands/iworker_command.hpp"
#include "../../include/commands/abstract_worker_command.hpp"
#include "../../include/commands/remove_iscsi_target_command.hpp"
#include <string>
namespace gorynych{
    namespace workers{

        RemoveIscsiTargetWorkerCommand::RemoveIscsiTargetWorkerCommand(const std::string targetName) :
                AbstractWorkerCommand(WorkerCommandType::REMOVE_TARGET), targetName_(targetName) {
        }

        const std::string &RemoveIscsiTargetWorkerCommand::targetName() const {
            return targetName_;
        }
    }


}

