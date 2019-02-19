#include "../../include/commands/disconnect_device_to_iscsi_target_worker_command.hpp"

namespace gorynych {
    namespace workers {

        DisconnectDeviceToIscsiTargetWorkerCommand::DisconnectDeviceToIscsiTargetWorkerCommand(
                    const std::string &targetName, const unsigned int lunNumber)
                : AbstractWorkerCommand(WorkerCommandType::DISCONNECT_DEVICE_TO_ISCSI_TARGET),
                  targetName_(targetName),
                  lunNumber_(lunNumber) {

        }



    }
}

