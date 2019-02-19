#include <boost/algorithm/string/replace.hpp>
#include "../../include/scst/disconnect_device_to_iscsi_target_worker.hpp"

namespace gorynych {
    namespace workers {
        DisconnectDeviceToIscsiTargetWorker::DisconnectDeviceToIscsiTargetWorker(const unsigned int id,
                                                                                 const DisconnectDeviceToIscsiTargetWorkerCommand &command)
                : AbstractScstWorker(id, WORKER_TYPE::DISCONNECT_DEVICE_TO_ISCSI_TARGET_WORKER), command_(command) {};

        DisconnectDeviceToIscsiTargetWorkerResponse &DisconnectDeviceToIscsiTargetWorker::doWork() {
            DisconnectDeviceToIscsiTargetWorkerResponse *response;
            if (writeToSysFs(generatePathForDisconnectDeviceToTargetCommand(), generateStringForDisconnectDeviceToTargetCommand())) {
                response = new DisconnectDeviceToIscsiTargetWorkerResponse(true);
            } else{
                response = new DisconnectDeviceToIscsiTargetWorkerResponse(false, generateSystemErrorMessage(),
                                                                           generateProgrammerErrorMessage());
            }
            return *response;
        }


        void DisconnectDeviceToIscsiTargetWorker::sendNotification() {

        }

        const std::string DisconnectDeviceToIscsiTargetWorker::generateSystemErrorMessage() {
            return "";
        }

        const std::string DisconnectDeviceToIscsiTargetWorker::generateProgrammerErrorMessage() {
            return "";
        }

        const std::string DisconnectDeviceToIscsiTargetWorker::generatePathForDisconnectDeviceToTargetCommand() const {
            auto magicString1 = "/sys/kernel/scst_tgt/targets/iscsi/";
            auto magicString2 = "/luns/mgmt";
            return magicString1 + command_.targetName() + magicString2;
        }

        const std::string DisconnectDeviceToIscsiTargetWorker::generateStringForDisconnectDeviceToTargetCommand() {
            auto magicString = "del ";
            return magicString + std::to_string(command_.lunNumber());


        }

    }
}
