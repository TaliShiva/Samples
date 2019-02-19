//
// Created by dumplings on 14.03.17.
//

#include <boost/algorithm/string/replace.hpp>
#include "../../include/scst/connect_device_to_iscsi_target_worker.hpp"


namespace gorynych {
    namespace workers {
        
        ConnectDeviceToIscsiTargetWorker::ConnectDeviceToIscsiTargetWorker(const unsigned int id,
                                                                           const ConnectDeviceToIscsiTargetWorkerCommand &command)
                : AbstractScstWorker(id, WORKER_TYPE::CONNECT_DEVICE_TO_ISCSI_TARGET_WORKER), command_(command) {
        }

        ConnectDeviceToIscsiTargetWorkerResponse &ConnectDeviceToIscsiTargetWorker::doWork() {
            ConnectDeviceToIscsiTargetWorkerResponse *response;
            if (writeToSysFs(generatePathForConnectDeviceToTargetCommand(),
                             generateStringForConnectDeviceToTargetCommand())) {
                response = new ConnectDeviceToIscsiTargetWorkerResponse(true);
            } else {
                response = new ConnectDeviceToIscsiTargetWorkerResponse(false, "unknown error",
                                                                        "cannot connect device to target");
            }
            return *response; //FIXME заменить на shared_pointer

        }

        void ConnectDeviceToIscsiTargetWorker::sendNotification() {}

        const std::string ConnectDeviceToIscsiTargetWorker::generatePathForConnectDeviceToTargetCommand() const {
            auto pathSuffix = "/luns/mgmt";
            return iscsiTargetsPathPrefix_ + command_.targetName() + pathSuffix;
       }

        const std::string ConnectDeviceToIscsiTargetWorker::generateStringForConnectDeviceToTargetCommand()  {
            auto magicString1 = "add ";
            auto magicString2 = " read_only=0";
            return magicString1 + command_.vDiskName() + " "
                   + std::to_string(command_.lunNumber()) + magicString2;

        }
        const std::string ConnectDeviceToIscsiTargetWorker::generateSystemErrorMessage() {
            return "";
        }

        const std::string ConnectDeviceToIscsiTargetWorker::generateProgrammerErrorMessage() {
            return "";
        }
    }
}