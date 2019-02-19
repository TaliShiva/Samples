#include "../include/worker_manager.hpp"
#include "../../workers/include/scst/remove_disk_from_scst_worker.hpp"
#include "../../workers/include/scst/remove_iscsi_target_worker.hpp"
#include "../../workers/include/close_worker.hpp"
#include "../../workers/include/scst/connect_device_to_iscsi_target_worker.hpp"
#include "../../workers/include/scst/disconnect_device_to_iscsi_target_worker.hpp"

#include "../../workers/include/scst/enable_iscsi_target_worker.hpp"
#include "../../utils/include/build__scst_vdisk_name.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace transport;
        using namespace utils;
        WorkerManager::WorkerManager() {
            init();
        }

        WorkerManager::~WorkerManager() {

        }

        IResponse &WorkerManager::runOpenWorker(const unsigned int id, const OpenCommand &command) {
            OpenWorker *worker = dynamic_cast<OpenWorker *>(openWorkerFactory_.createWorker(
                    id));//создаем нового исполнителя
            worker->init(command);
            return worker->doWork();
        }

        IResponse &WorkerManager::runCloseWorker(const unsigned int id, const CloseCommand &command) {
            CloseWorker *worker = dynamic_cast<CloseWorker*>(closeWorkerFactory_.createWorker(id));//создаем нового исполнителя
            worker->init(command);
            //delete worker;  <- это крашит программу
            return worker->doWork();
        }

        void WorkerManager::init() {
        }

        CreateTargetWorkerResponse &WorkerManager::runCreateIscsiTargetWorker(const unsigned int id,
                                                                              const CreateTargetWorkerCommand &command) {
            createIscsiTargetWorkerFactory_.init(command);
            CreateIscsiTargetWorker *worker
                    = dynamic_cast<CreateIscsiTargetWorker *>(createIscsiTargetWorkerFactory_.createWorker(id));
            CreateTargetWorkerResponse &response = worker->doWork();
            //delete worker; FIXME починить утечку памяти
            return response;
        }

        EnableIscsiTargetWorkerResponse &WorkerManager::runEnableIscsiTargetWorker(const unsigned int id,
                                                                                   const EnableIscsiTargetWorkerCommand &command) {
            EnableIscsiTargetWorkerCommand workerCommand(command.targetName());
            enableIscsiTargetWorkerFactory_.init(workerCommand);

            EnableIscsiTargetWorker *worker = dynamic_cast<EnableIscsiTargetWorker *>(enableIscsiTargetWorkerFactory_.createWorker(
                    id));
            return worker->doWork();
        }

        CreateRaidWorkerResponse &
        WorkerManager::runCreateRaidWorker(const unsigned int id, const CreateRaidWorkerCommand &command) {
            createRaidWorkerFactory_.init(command);
            CreateRaidWorker *worker = dynamic_cast<CreateRaidWorker *>(createRaidWorkerFactory_.createWorker(
                    id));
            CreateRaidWorkerResponse &response = worker->doWork();
            //delete worker; FIXME починить утечку памяти
            return response;
        }

        RemoveIscsiTargetWorkerResponse &
        WorkerManager::runRemoveIscsiTargetWorker(const uint id, const RemoveIscsiTargetCommand &command) {
            RemoveIscsiTargetWorkerCommand removeIscsiTargetWorkerCommand(command.targetName());
            RemoveIscsiTargetWorker *worker = new RemoveIscsiTargetWorker(id, removeIscsiTargetWorkerCommand);
            RemoveIscsiTargetWorkerResponse &response = worker->doWork();
            return response;
//            return dynamic_cast<RemoveIscsiTargetWorkerResponse &>(removeIscsiTargetWorkerFactory_.createWorker(
//                    id)->doWork());
        }

        RemoveDiskFromScstWorkerResponse
        WorkerManager::runRemoveDiskFromScstWorker(const unsigned int id,
                                                   const RemoveDiskFromScstCommand &removeCommand) {
            RemoveDiskFromScstWorkerCommand command(buildScstVdiskName(removeCommand.devicePath()));
            RemoveDiskFromScstWorker *worker = new RemoveDiskFromScstWorker(id, command);
            return worker->doWork();
        }

        AddDiskToScstWorkerResponse &WorkerManager::runAddDiskToScstWorker(const unsigned int id,
                                                                           const AddDiskToScstWorkerCommand &command) {

            AddDiskToScstWorker *addDiskToScstWorker = new AddDiskToScstWorker(id, command);

            AddDiskToScstWorkerResponse &response = addDiskToScstWorker->doWork();
            delete addDiskToScstWorker;
            return response;
        }

        DestroyRaidWorkerResponse &
        WorkerManager::runDestroyRaidWorker(const unsigned int id, const DestroyRaidWorkerCommand &command) {
            destroyRaidWorkerFactory_.init(command);
            DestroyRaidWorker *worker = dynamic_cast<DestroyRaidWorker *>(destroyRaidWorkerFactory_.createWorker(
                    id));
            DestroyRaidWorkerResponse &response = worker->doWork();
            //delete worker; FIXME починить утечку памяти
            return response;
        }

        CreateLvmWorkerResponse &
        WorkerManager::runCreateLvmWorker(const unsigned int id, const CreateLvmWorkerCommand &command) {
            createLvmWorkerFactory_.init(command);
            CreateLvmWorker *worker = dynamic_cast<CreateLvmWorker *>(createLvmWorkerFactory_.createWorker(
                    id));
            CreateLvmWorkerResponse &response = worker->doWork();
            //delete worker;
            return response;
        }

        DestroyLvmWorkerResponse &
        WorkerManager::runDestroyLvmWorker(const unsigned int id, const DestroyLvmWorkerCommand &command) {
            destroyLvmWorkerFactory_.init(command);
            DestroyLvmWorker *worker = dynamic_cast<DestroyLvmWorker *>(destroyLvmWorkerFactory_.createWorker(
                    id));
            DestroyLvmWorkerResponse &response = worker->doWork();
            //delete worker; FIXME починить утечку памяти
            return response;
        }

        DeleteLogicalVolumeWorkerResponse &
        WorkerManager::runDeleteLogicalVolumeWorker(const unsigned int id,
                                                    const DeleteLogicalVolumeWorkerCommand &command) {
            deleteLogicalVolumeWorkerFactory_.init(command);
            DeleteLogicalVolumeWorker *worker = dynamic_cast<DeleteLogicalVolumeWorker *>(deleteLogicalVolumeWorkerFactory_.createWorker(
                    id));
            DeleteLogicalVolumeWorkerResponse &response = worker->doWork();
            //delete worker; FIXME починить утечку памяти
            return response;
        }

        DisableIscsiTargetWorkerResponse &WorkerManager::runDisableIscsiTargetWorker(const unsigned int id,
                                                                                     const DisableIscsiTargetWorkerCommand &command) {
            disableIscsiTargetWorkerFactory_.init(command);
            DisableIscsiTargetWorker *worker
                    = dynamic_cast<DisableIscsiTargetWorker *>(disableIscsiTargetWorkerFactory_.createWorker(id));
            return worker->doWork();
        }

        ConnectDeviceToIscsiTargetWorkerResponse
        WorkerManager::runConnectDeviceToIscsiTargetWorker(const unsigned int id,
                                                           const ConnectDeviceToIscsiTargetWorkerCommand &command) {
            connectDeviceToIscsiTargetWorkerFactory_.init(command);
            ConnectDeviceToIscsiTargetWorker *worker =
                    dynamic_cast<ConnectDeviceToIscsiTargetWorker *>(connectDeviceToIscsiTargetWorkerFactory_.
                            createWorker(id));


            return worker->doWork();
        }

        DisconnectDeviceToIscsiTargetWorkerResponse
        WorkerManager::runDisconnectDeviceToIscsiTargetWorker(const unsigned int id,
                                                              const DisconnectDeviceToIscsiTargetWorkerCommand &command) {
            disconnectDeviceToIscsiTargetWorkerFactory_.init(command);
            DisconnectDeviceToIscsiTargetWorker *worker = dynamic_cast<DisconnectDeviceToIscsiTargetWorker *> (disconnectDeviceToIscsiTargetWorkerFactory_.createWorker(
                    id));
            return worker->doWork();
        }


    }
}
