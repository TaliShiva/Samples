//
// Created by boa on 13.03.17.
//

#pragma once

#include "abstract_worker_command.hpp"
#include <string>
namespace gorynych{
    namespace workers{
        /**
         * @see documentation AbstractWorkerCommand
         */
        class RemoveIscsiTargetWorkerCommand : public AbstractWorkerCommand {
        public:
            RemoveIscsiTargetWorkerCommand(const std::string targetName);
            RemoveIscsiTargetWorkerCommand() : AbstractWorkerCommand(WorkerCommandType::REMOVE_TARGET) {}
        private:
            const std::string targetName_;
        public:
            const std::string &targetName() const;

        };
    }
}
