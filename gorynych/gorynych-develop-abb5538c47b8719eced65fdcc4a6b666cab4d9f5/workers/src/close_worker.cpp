#include <fstream>
#include "../include/close_worker.hpp"
namespace gorynych {
    namespace workers {
        CloseWorker::CloseWorker(const unsigned int id,
                                 const WORKER_TYPE_OLD workerType)
                : AbstractWorkerOld(id, workerType) {
        }

        IResponse &CloseWorker::doWork() {
            auto setErrorMessage = [this](std::string message) mutable {
                response_.setSystemErrorMessage(message + lastError_);
                response_.setSuccess(false);
            };

            if (removeLun() != 0) {
                setErrorMessage(
                        "cannot remove lun\t" + std::to_string(lunNumber_) + "\t" + targetName_ + "\t" + devicePath_);
                return response_;
            }
            if (removeTarget() != 0) {
                setErrorMessage("cannot remove target\t" + targetName_ + "\t" + devicePath_);
                return response_;
            }
            if (removeDisk() != 0) {
                setErrorMessage("cannot remove disk\t" + devicePath_);
                return response_;
            }
            response_.setSuccess(true);
            return response_;
        }

        void CloseWorker::sendNotification() {

        }

        int CloseWorker::removeLun() {
            std::ofstream device;
            device.open(generatePathForRemoveLun());
            if (device.is_open()) {
//                device << "del " + std::to_string(lunNumber_);
                device << generateRemoveLunString();
                device.close();
                return 0;
            }
            getLastSystemError();
            return -1;
        }

        int CloseWorker::removeTarget() {
            std::ofstream device;
            device.open(iscsiPath_);
            if (device.is_open()) {
                device << generateRemoveTargetString();
                device.close();
                return 0;
            }
            getLastSystemError();
            return -1;
        }

        int CloseWorker::removeDisk() {
            std::ofstream device;
            device.open(vDiskPath_);
            if (device.is_open()) {
                device << generateRemoveDiskString();
                device.close();
            }
            return 0;
        }

        void CloseWorker::init(const CloseCommand &command) {
            setDevicePath(command.devicePath());
            setTargetName(command.targetName());
            setLun(command.lun());
        }

        void CloseWorker::getLastSystemError() {
            lastError_ = "|";
        }

        const std::string CloseWorker::generatePathForRemoveLun() const {
            auto magicString1 = "/sys/kernel/scst_tgt/targets/iscsi/";
            auto magicString2 = "/luns/mgmt";
            return magicString1 + targetName_ + magicString2;
        }

        const std::string CloseWorker::generateRemoveLunString() const {
            auto magicString = "del ";
            return magicString + std::to_string(lunNumber_);
        }

        const std::string CloseWorker::generateRemoveTargetString() const {
            auto magicString = "del_target ";
            return magicString + targetName_;
        }

        const std::string CloseWorker::generateRemoveDiskString() const {
            auto magicString = "del_device ";
            return magicString + deviceScstName_;
        }
    }
}
