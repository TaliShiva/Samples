#include "../include/open_worker.hpp"
#include <cstdlib>
#include <fstream>
namespace gorynych {
    namespace workers {
        OpenWorker::OpenWorker(const unsigned int id,
                               const WORKER_TYPE_OLD workerType)
                : AbstractWorkerOld(id, workerType) {

        }

        IResponse &OpenWorker::doWork() {
            auto setErrorMessage = [this](std::string message) mutable {
                response_.setSystemErrorMessage(message + lastError_);
                response_.setSuccess(false);
            };
            if (addDevice() != 0) {
                setErrorMessage("cannot add device");
                return response_;
            }
            if (createTarget() != 0) {
                setErrorMessage("cannot create target");
                return response_;
            }
            if (connectDeviceToTarget() != 0) {
                setErrorMessage("failed to connect the device to target");
                response_.setSystemErrorMessage("");
                return response_;
            }
            if (enableTarget() != 0) {
                setErrorMessage("cannot enable target");
                return response_;
            }

            response_.setSuccess(true);
            return response_;
        }

        void OpenWorker::sendNotification() {

        }

        int OpenWorker::addDevice() {
            std::ofstream device;
            device.open(fileIoHandlerPath_);
            if (device.is_open()) {
                device << generateStringForAddCommand();
                device.close();
                return 0;
            }
            return -1;
        }

        int OpenWorker::createTarget() {
            std::ofstream device;
            device.open(iscsiPath_);
            if (device.is_open()) {
                device << generateStringForCreateTargetCommand();
                device.close();
                return 0;
            }
            return -1;
        }

        int OpenWorker::connectDeviceToTarget() {
            std::ofstream device;
            device.open(generatePathForConnectDeviceToTargetCommand());
            if (device.is_open()) {
                device << generateStringForConnectDeviceToTargetCommand();
                device.close();
                return 0;
            }
            return -1;
        }

        int OpenWorker::enableTarget() {
            std::ofstream device;
            device.open(generatePathForEnableTargetCommand());
            if (device.is_open()) {
                device << "1";
                device.close();
                return 0;
            }
            return -1;
        }

        const std::string OpenWorker::generateStringForAddCommand() const {
            auto magicString1 = "add_device ";
            auto magicString2 = " filename=";
            auto magicString3 = "; nv_cache=1";
            return magicString1 + deviceScstName_ + magicString2 + devicePath_ + magicString3;
        }

        const std::string OpenWorker::generateStringForCreateTargetCommand() const {
            auto magicString = "add_target ";
            return magicString + targetName_;
        }

        const std::string OpenWorker::generatePathForConnectDeviceToTargetCommand() const {
            auto pathSuffix = "/luns/mgmt";
            return pathPrefix_ + targetName_ + pathSuffix;
        }

        const std::string OpenWorker::generatePathForEnableTargetCommand() const {
            auto pathSuffix = "/enabled";
            return pathPrefix_ + targetName_ + pathSuffix;
        }

        const std::string OpenWorker::generateStringForConnectDeviceToTargetCommand() const {
            auto magicString1 = "add ";
            auto magicString2 = " read_only=0";
            return magicString1 + deviceScstName_ + " " + std::to_string(lunNumber_) + magicString2;
        }

        void OpenWorker::init(const OpenCommand &command) {
            setDevicePath(command.devicePath());
            setTargetName(command.targetName());
            setLun(command.lun());
        }
    }
}
