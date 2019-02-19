//
// Created by dumplings on 14.03.17.
//
#pragma once

#include <string>

#include "abstract_worker_command.hpp"

namespace gorynych {
    namespace workers {///home/oleg/ClionProjects/single_controller_storage_system/workers/include/commands/create_lun_to_iscsi_target_worker_command.hpp
        class ConnectDeviceToIscsiTargetWorkerCommand : public AbstractWorkerCommand {

        public:
            ConnectDeviceToIscsiTargetWorkerCommand(const std::string &targetName,
                                                    const std::string &vDiskName,
                                                    const unsigned int lunNumber);
        public:
            const std::string &targetName() const {
                return targetName_;
            }

            const std::string &vDiskName() const {
                return vDiskName_;
            }

            const unsigned int lunNumber() const {
                return lunNumber_;
            }

        private:
            const std::string targetName_;
            const std::string vDiskName_;
            const unsigned int lunNumber_;
        };
    }
}