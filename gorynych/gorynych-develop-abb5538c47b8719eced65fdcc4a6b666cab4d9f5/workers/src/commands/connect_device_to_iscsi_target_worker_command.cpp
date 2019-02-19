//
// Created by oleg on 20.03.17.
//

#include "../../include/commands/connect_device_to_iscsi_target_worker_command.hpp"

namespace gorynych {
    namespace workers {

        ConnectDeviceToIscsiTargetWorkerCommand::ConnectDeviceToIscsiTargetWorkerCommand(const std::string &targetName,
                                                                                         const std::string &vDiskName,
                                                                                         const unsigned int lunNumber)
                : AbstractWorkerCommand(WorkerCommandType::CONNECT_DEVICE_TO_ISCSI_TARGET), targetName_(targetName),
                  vDiskName_(vDiskName), lunNumber_(lunNumber) {
        }
    }
}