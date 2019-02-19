#pragma once

#include "abstract_worker_command.hpp"
#include <string>

namespace gorynych {
    namespace workers {
        class DisconnectDeviceToIscsiTargetWorkerCommand : public AbstractWorkerCommand {
        public:
            DisconnectDeviceToIscsiTargetWorkerCommand(
                        const std::string &targetName, const unsigned int lunNumber);

            const std::string &targetName() const {
                return targetName_;
            }

            const unsigned int lunNumber() const {
                return lunNumber_;
            }

        private:
            const std::string targetName_;
            const unsigned int lunNumber_;
        };
    }
}