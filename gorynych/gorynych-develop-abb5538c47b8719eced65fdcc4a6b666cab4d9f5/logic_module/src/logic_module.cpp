
#include "../include/logic_module.hpp"
#include "../../workers/include/responses/create_logical_volume_response.hpp"
#include "../../workers/include/commands/create_logical_volume_worker_command.hpp"
#include "../../workers/include/lvm/create_logical_volume_worker.hpp"
#include "../../workers/include/commands/disable_iscsi_target_worker_command.hpp"
#include "../../workers/include/responses/disable_iscsi_target_worker_response.hpp"
#include "../../workers/include/responses/disconnect_device_to_iscsi_worker_response.hpp"
#include "../../workers/include/commands/disconnect_device_to_iscsi_target_worker_command.hpp"
#include "../../workers/include/bcache/create_cached_disk_worker.hpp"
#include "../../workers/include/bcache/detach_cached_disk_worker.hpp"
#include "../../workers/include/scst/remove_iscsi_target_worker.hpp"
#include "../../utils/include/build__scst_vdisk_name.hpp"
#include "../../utils/include/bcache_utils.hpp"
#include <boost/algorithm/string.hpp>


namespace gorynych {
    namespace logic {
        using namespace transport;
        using namespace worker_manager;
        using namespace workers;
        using namespace utils;
        Logic::Logic() : systemState_(new SystemState()) {
            workerManager_ = WorkerManager::getInstance();
        }

        TextResponse Logic::buildTextResponse(const AbstractWorkerResponse &workerResponse) {
            TextResponse textResponse;
            textResponse.setSuccess(workerResponse.isSuccess());
            textResponse.setLogicErrorMessage(workerResponse.programmerErrorMessage());
            textResponse.setSystemErrorMessage(workerResponse.systemErrorMessage());
            return textResponse;
        }

        TextResponse
        Logic::buildTextResponse(bool success, const std::string &programmerError, const std::string &systemError) {
            TextResponse response;
            response.setSuccess(success);
            response.setLogicErrorMessage(programmerError);
            response.setSystemErrorMessage(systemError);
            return response;
        }

        TextResponse Logic::execution(const CloseCommand &command) {
            return dynamic_cast<TextResponse &>(WorkerManager::getInstance()->runCloseWorker(Logic::createNewId(),
                                                                                             command));//
        }

        TextResponse Logic::execution(const OpenCommand &command) {
            return dynamic_cast<TextResponse &>(WorkerManager::getInstance()->runOpenWorker(Logic::createNewId(),
                                                                                            command));
        }


        unsigned int Logic::createNewId() {
            return ++id_;
        }

        unsigned int Logic::id_ = 0;

        TextResponse Logic::execution(const CreateIscsiTargetCommand &command) {
            CreateTargetWorkerCommand workerCommand(command.targetName());
            auto response = workerManager_->runCreateIscsiTargetWorker(Logic::createNewId(), workerCommand);
            if (response.isSuccess()) {
                systemState_->addIscsiTarget(command.targetName());
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const ConnectDeviceToIscsiTargetCommand &command) {
            bool success;
            std::string lvName;
            std::string vgName;
            std::tie(success, vgName, lvName) = parseDevicePath(command.devicePath());
            if (!success) {
                return buildTextResponse(false, "Error! Wrong device path. Need /dev/{Volume Group}/{Logical Volume}", "");
            }
            if (!systemState_->isLogicalVolumeExists(lvName, vgName)) {
                return buildTextResponse(false, "Error! logical volume in path " + command.devicePath() + " not exist","");
            }
            auto vDiskName = buildScstVdiskName(command.devicePath());
            ConnectDeviceToIscsiTargetWorkerCommand workerCommand(command.targetName(),
                                                                  vDiskName,
                                                                  command.lunNumber());
            auto response = workerManager_->runConnectDeviceToIscsiTargetWorker(Logic::createNewId(), workerCommand);
            if (response.isSuccess()) {
                systemState_->addLun(command.targetName(), command.lunNumber(), vDiskName);
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const AddDiskToScstCommand &command) {
            bool success;
            std::string lvName;
            std::string vgName;
            std::tie(success, vgName, lvName) = parseDevicePath(command.devicePath());
            if (!success) {
                return buildTextResponse(false, "Error! Wrong device path. Need /dev/{Volume Group}/{Logical Volume}", "");
            }
            if (!systemState_->isLogicalVolumeExists(lvName, vgName)) {
                return buildTextResponse(false, "Error! logical volume in path " + command.devicePath() + " not exist","");
            }
            std::string trueDevicePath = command.devicePath();
            if (systemState_->isCached(lvName, vgName)) {
                trueDevicePath = getBcacheIndexFromPath(command.devicePath());
            }
            AddDiskToScstWorkerCommand addDiskToScstWorkerCommand(trueDevicePath, buildScstVdiskName(command.devicePath()));
            auto response = workerManager_->runAddDiskToScstWorker(Logic::createNewId(), addDiskToScstWorkerCommand);
            if (response.isSuccess()) {
                systemState_->setVdiskName(lvName,vgName,buildScstVdiskName(command.devicePath()));
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const RemoveIscsiTargetCommand &command) {
            RemoveIscsiTargetWorkerCommand workerCommand(command.targetName());
            auto *worker = new RemoveIscsiTargetWorker(Logic::createNewId(), workerCommand);
            RemoveIscsiTargetWorkerResponse &response = worker->doWork();
            if(response.isSuccess()) {
                systemState_->deleteIscsiTarget(command.targetName());
            }
            return buildTextResponse(response);
        }


        TextResponse Logic::execution(const RemoveDiskFromScstCommand &command) {
            bool success;
            std::string lvName;
            std::string vgName;
            std::tie(success, vgName, lvName) = parseDevicePath(command.devicePath());
/*            std::cout << "success: " << (success ? "true" : "false") << std::endl;
            std::cout << "vgName: " << vgName << std::endl;
            std::cout << "lvName: " << lvName << std::endl;*/
            if (!success) {
                return buildTextResponse(false, "Error! Wrong device path. Need /dev/{Volume Group}/{Logical Volume}", "");
            }
            if (!systemState_->isLogicalVolumeExists(lvName, vgName)) {
                return buildTextResponse(false, "Error! logical volume in path " + command.devicePath() + " not exist","");
            }
            auto response = workerManager_->runRemoveDiskFromScstWorker(Logic::createNewId(), command);
            if (response.isSuccess()) {
                systemState_->unsetVdiskName(lvName,vgName);
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const CreateRaidCommand &command) {
            CreateRaidWorkerCommand workerCommand(command.deviceCount(),
                                                  command.raidLevel(),
                                                  command.devices(),
                                                  command.raidPath());
            auto response = workerManager_->runCreateRaidWorker(Logic::createNewId(), workerCommand);
            if (response.isSuccess()) {
                systemState_->addRaid(command.raidPath(), std::to_string(command.raidLevel()), command.devices());
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const DestroyRaidCommand &command) {
            DestroyRaidWorkerCommand workerCommand(systemState_->getRaidDevices(command.raidPath()),
                                                   command.raidPath());
            auto response = workerManager_->runDestroyRaidWorker(Logic::createNewId(), workerCommand);
            if (response.isSuccess()) {
                systemState_->deleteRaid(command.raidPath());
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const CreateLvmCommand &command) {
            CreateLvmWorkerCommand workerCommand(command.volumeGroupName(), command.devicePath());
            auto response = workerManager_->runCreateLvmWorker(Logic::createNewId(), workerCommand);
            if (response.isSuccess()) {
                systemState_->setRaidVolumeGroup(command.devicePath(), command.volumeGroupName());//FIXME добавить проверку на существование рэйда
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const DeleteLogicalVolumeCommand &command) {
            DeleteLogicalVolumeWorkerCommand workerCommand(command.volumeGroupName(), command.logicalVolumeName());
            auto response = workerManager_->runDeleteLogicalVolumeWorker(Logic::createNewId(), workerCommand);
            if (response.isSuccess()) {
                systemState_->deleteLogicalVolume(command.logicalVolumeName(), command.volumeGroupName());
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const CreateLogicalVolumeCommand &command) {
            const std::string lvName = command.logicalVolumeName();
            const std::string lvSize = command.logicalVolumeSize();
            const std::string vgName = command.parentVolumeGroupName();
            CreateLogicalVolumeWorkerCommand workerCommand(lvName, lvSize, vgName);
            CreateLogicalVolumeWorker *worker = new CreateLogicalVolumeWorker(Logic::createNewId(), workerCommand);
            auto response = worker->doWork();
            if (response.isSuccess()) {
                systemState_->addLogicalVolume(lvName, vgName, lvSize);
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const DestroyLvmCommand &command) {
            DestroyLvmWorkerCommand workerCommand(command.volumeGroupName(), command.devicePath());
            auto response = workerManager_->runDestroyLvmWorker(Logic::createNewId(), workerCommand);
            if(response.isSuccess()) {
                systemState_->unsetRaidVolumeGroup(command.devicePath());
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const CreateCachedDiskCommand &command) {
            bool success;
            std::string lvName;
            std::string vgName;
            std::tie(success, vgName, lvName) = parseDevicePath(command.baseDevicePath());
            if (!success) {
                return buildTextResponse(false, "Error! Wrong base device path. Need /dev/{Volume Group}/{Logical Volume}", "");
            }
            if (!systemState_->isLogicalVolumeExists(lvName, vgName)) {
                return buildTextResponse(false, "Error! logical volume in path " + command.baseDevicePath() + " not exist", "");
            }
            if (systemState_->isCached(lvName, vgName)) {
                return buildTextResponse(false, "Error! cache already connected to device in path " + command.baseDevicePath(), "");
            }
            CachingAlgorithm cachingAlgorithm;
            CachingMode cachingMode;
            if(command.cachingAlgorithm() == "fifo") {
                cachingAlgorithm = CachingAlgorithm::FIFO;
            } else if(command.cachingAlgorithm() == "random") {
                cachingAlgorithm = CachingAlgorithm::Random;
            } else {
                cachingAlgorithm = CachingAlgorithm::LRU;
            }
            if(command.cachingMode() == "Writeback") {
                cachingMode = CachingMode::Writeback;
            } else {
                cachingMode = CachingMode::Writethrough;
            }
            CreateCachedDiskWorkerCommand workerCommand(command.baseDevicePath(), command.cachingDevicePath(),
                                                        cachingAlgorithm, cachingMode);
            CreateCachedDiskWorker worker(Logic::createNewId(), workerCommand);
            SilentWorkerResponse *response = worker.doWork();
            if (response->isSuccess()) {
                systemState_->setCache(lvName, vgName, command.cachingDevicePath());
            }
            TextResponse textResponse;
            textResponse.setSuccess(response->isSuccess());
            textResponse.setLogicErrorMessage(response->programmerErrorMessage());
            textResponse.setSystemErrorMessage(response->systemErrorMessage());
            delete response;
            return textResponse;
        }

        TextResponse Logic::execution(const DetachCachedDiskCommand &command) { //FIXME убрать из команды параметр cachingDevicePath
            bool success;
            std::string lvName;
            std::string vgName;
            std::tie(success, vgName, lvName) = parseDevicePath(command.baseDevicePath());
            if (!success) {
                return buildTextResponse(false, "Error! Wrong base device path. Need /dev/{Volume Group}/{Logical Volume}", "");
            }
            if (!systemState_->isLogicalVolumeExists(lvName, vgName)) {
                return buildTextResponse(false, "Error! logical volume in path " + command.baseDevicePath() + " not exist", "");
            }
            if (!systemState_->isCached(lvName, vgName)) {
                return buildTextResponse(false, "Error! cache not connected to device in path " + command.baseDevicePath(), "");
            }
            DetachCachedDiskWorkerCommand workerCommand(command.baseDevicePath(),
                                                        systemState_->getCachingDevicePath(lvName, vgName));
            if(systemState_->getCachingDevicePath(lvName, vgName) != command.cachingDevicePath()) {
                std::cerr << "Попытка удалить кэш на неправильном caching device" << std::endl;
            }
            DetachCachedDiskWorker worker(Logic::createNewId(), workerCommand);
            SilentWorkerResponse *response = worker.doWork();
            if (response->isSuccess()) {
                systemState_->unsetCache(lvName, vgName);
            }
            TextResponse textResponse;
            textResponse.setSuccess(response->isSuccess());
            textResponse.setLogicErrorMessage(response->programmerErrorMessage());
            textResponse.setSystemErrorMessage(response->systemErrorMessage());
            delete response;
            return textResponse;
        }

        TextResponse Logic::execution(const DisableIscsiTargetCommand &command) {
            DisableIscsiTargetWorkerCommand workerCommand(command.targetName());
            auto response = workerManager_->runDisableIscsiTargetWorker(Logic::createNewId(), workerCommand);
            if(response.isSuccess()) {
                systemState_->disableIscsiTarget(command.targetName());
            }
            return buildTextResponse(response);
        }

        TextResponse Logic::execution(const DisconnectDeviceToIscsiTargetCommand &command) {
                        DisconnectDeviceToIscsiTargetWorkerCommand workerCommand(command.targetName(), command.lunNumber());
            auto response = workerManager_->runDisconnectDeviceToIscsiTargetWorker(Logic::createNewId(),
                                                                                   workerCommand);
            if (response.isSuccess()) {
                systemState_->deleteLun(command.targetName(), command.lunNumber());
            }
            return buildTextResponse(response);
        }

        const ListRaidResponse Logic::execution(const ListRaidCommand &command) {
            ListRaidResponse response;
            //StringVector stringVector = {"/dev/sda", "/dev/sdb"};
            response.setRaidItemList(systemState_->getRaidList());
            return response;
        }

        const ListLogicalVolumeResponse Logic::execution(const ListLogicalVolumeCommand &command) {

            ListLogicalVolumeResponse response;
            response.setLogicalVolumeItemList(systemState_->getLogicalVolumeList());
            return response;
        }

        const ListScstResponse Logic::execution(const ListScstCommand &command) {
            ListScstResponse response;
            response.setTargetItemList(systemState_->getTargetList());
            return response;
        }

        TextResponse Logic::execution(const EnableIscsiTargetCommand &command) {
            EnableIscsiTargetWorkerCommand workerCommand(command.targetName());
            EnableIscsiTargetWorkerResponse response = WorkerManager::getInstance()->runEnableIscsiTargetWorker(
                    Logic::createNewId(), workerCommand);
            if(response.isSuccess()) {
                systemState_->enableIscsiTarget(command.targetName());
            }
            return buildTextResponse(response);
        }

        /**
         * @brief Метод ожидает получить путь в формате /dev/{Volume_Group_Name}/{Logical_Volume_Name}
         * @param path - путь к logical Volume
         * @return TupleErrorLvNameVgName - первый элемент tuple равен false, если path не соответствует условиям
         */
        Logic::TupleSuccessVgNameLvName Logic::parseDevicePath(const std::string &path) {
            using namespace boost::algorithm;
            std::vector<std::string> split_output;
            const int splitCount = 4;//first item in split_output is empty
            split(split_output, path, is_any_of("/"));
            bool success = true;
            if(split_output.size() != splitCount){
                success = false;
                return std::make_tuple(success, "", "");
            }
            return std::make_tuple(success, split_output.at(2),split_output.at(3));
        }


    }
}



