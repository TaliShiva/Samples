#pragma once


#include "../../transport/include/command.hpp"
#include "open_worker_factory.hpp"
#include "close_worker_factory.hpp"
#include "../../transport/include/command/open.hpp"
#include "../../transport/include/command/close.hpp"
#include "worker_thread.hpp"
#include "factories/scst/create_iscsi_target_worker_factory.hpp"
#include "../../workers/include/responses/add_disk_to_scst_worker_response.hpp"
#include "../../workers/include/commands/add_disk_to_scst_worker_command.hpp"
#include "../../workers/include/scst/add_disk_to_scst_worker.hpp"
#include "factories/scst/remove_iscsi_target_worker_factory.hpp"
#include "../../workers/include/responses/remove_iscsi_target_worker_response.hpp"
#include "../../workers/include/commands/remove_iscsi_target_command.hpp"
#include "../../workers/include/commands/remove_disk_from_scst_worker_command.hpp"
#include "../../workers/include/responses/remove_disk_from_scst_worker_response.hpp"
#include "../../workers/include/commands/remove_iscsi_target_command.hpp"
#include "../../workers/include/commands/enable_iscsi_target_worker_command.hpp"
#include "../../workers/include/responses/enable_iscsi_target_worker_response.hpp"
#include "factories/md/create_raid_worker_factory.hpp"
#include "factories/md/destroy_raid_worker_factory.hpp"
#include "factories/lvm/create_lvm_worker_factory.hpp"
#include "factories/lvm/destroy_lvm_worker_factory.hpp"
#include "factories/scst/connect_device_to_iscsi_target_worker_factory.hpp"
#include "../../workers/include/responses/connect_device_to_iscsi_target_worker_response.hpp"
#include "factories/lvm/delete_logical_volume_worker_factory.hpp"
#include "../../workers/include/responses/delete_logical_volume_worker_response.hpp"
#include "../../workers/include/commands/delete_logical_volume_command.hpp"
#include "../../workers/include/lvm/delete_logical_volume_worker.hpp"
#include "../../workers/include/responses/disable_iscsi_target_worker_response.hpp"
#include "../../workers/include/commands/disable_iscsi_target_worker_command.hpp"
#include "factories/scst/disable_iscsi_target_worker_factory.hpp"
#include "../../workers/include/responses/disconnect_device_to_iscsi_worker_response.hpp"
#include "factories/scst/disconnect_device_to_iscsi_target_worker_factory.hpp"
#include "factories/scst/enable_iscsi_target_worker_factory.hpp"

namespace gorynych {

    namespace worker_manager {

        using namespace transport;

        /**
         * @class WorkerManager - модуль управления исполнителями
         */
        class WorkerManager {


            /**
             * @brief WorkerManager - конструктор по умолчанию
             * @param parent
             */
            WorkerManager();

        public:
            /**
             * @brief getInstance классическая реалиизация singleton от Скотта Мейерса
             * @return  указатель на объект класса  WorkerManager
             */
            static WorkerManager *getInstance() {
                static WorkerManager *instance;
                if (instance == nullptr) {
                    instance = new WorkerManager();
                }
                return instance;
            }

            /**
             * @brief ~WorkerManager - деструктор. Освобождение ресурсов, завершение работы потоков, ...
             */
            virtual ~WorkerManager();


            DisconnectDeviceToIscsiTargetWorkerResponse runDisconnectDeviceToIscsiTargetWorker(const unsigned int id,
                                                                                       const DisconnectDeviceToIscsiTargetWorkerCommand &command);

        public:
            /**
             * @brief runOpenWorker - создает новый экземпляр класса OpenWorker, передает ему параметры конфигурации,
             * запускает на выполнение
             * @param id - уникальный идентификатор исполнителя
             * @param command - команда, содержащая параметры конфигурации исполнителя
             * @return объект класса TextResponse, содержащий статус выполнения операции, описание системной ошибки,
             * описание ошибки программиста
             */
            IResponse &runOpenWorker(const unsigned int id, const OpenCommand &command);

            /**
             * @brief runCloseWorker - создает новый экземпляр класса CloseWorker, передает ему параметры конфигурации,
             * запускает на выполнение
             * @param id - уникальный идентификатор исполнителя
             * @param command - команда, содержащая параметры конфигурации исполнителя
             * @return объект класса TextResponse, содержащий статус выполнения операции, описание системной ошибки,
             * описание ошибки программиста
             */
            IResponse &runCloseWorker(const unsigned int id, const CloseCommand &command);

            /**
             *
             * @param id - уникальный идентификатор исполнителя
             * @param command - команда, содержащая параметры конфигурации исполнителя
             * @return объект класса TextResponse, содержащий статус выполнения операции, описание системной ошибки,
             * описание ошибки программиста
             */
            CreateTargetWorkerResponse &runCreateIscsiTargetWorker(const unsigned int id,
                                                                   const CreateTargetWorkerCommand &command);

            /**
             *
             * @param id - уникальный идентификатор исполнителя
             * @param command - команда, содержащая параметры конфигурации исполнителя
             * @return объект класса TextResponse, содержащий статус выполнения операции, описание системной ошибки,
             * описание ошибки программиста
             */
            AddDiskToScstWorkerResponse &runAddDiskToScstWorker(const unsigned int id,
                                                                const AddDiskToScstWorkerCommand &command);

            ConnectDeviceToIscsiTargetWorkerResponse
            runConnectDeviceToIscsiTargetWorker(const unsigned int id,
                                                const ConnectDeviceToIscsiTargetWorkerCommand &command);

            DisconnectDeviceToIscsiTargetWorkerResponse
            runDisconnectDeviceToIscsiTargetWorker(const unsigned int id,
                                                   const DisconnectDeviceToIscsiTargetCommand &command);

            RemoveIscsiTargetWorkerResponse
            &runRemoveIscsiTargetWorker(const uint id, const RemoveIscsiTargetCommand &command);

            RemoveDiskFromScstWorkerResponse
            runRemoveDiskFromScstWorker(const unsigned int id, const RemoveDiskFromScstCommand &removeCommand);

            /**
            * @param id - уникальный идентификатор исполнителя
            * @param command - команда, содержащая параметры конфигурации исполнителя
            * @return объект класса CreateRaidWorkerResponse, содержащий статус выполнения операции, описание системной ошибки,
            * описание ошибки программиста
            */

            CreateRaidWorkerResponse &
            runCreateRaidWorker(const unsigned int id, const CreateRaidWorkerCommand &command);

            CreateLvmWorkerResponse &
            runCreateLvmWorker(const unsigned int id, const CreateLvmWorkerCommand &command);

            DestroyLvmWorkerResponse &
            runDestroyLvmWorker(const unsigned int id, const DestroyLvmWorkerCommand &command);


            DestroyRaidWorkerResponse &
            runDestroyRaidWorker(const unsigned int id, const DestroyRaidWorkerCommand &command);

            DeleteLogicalVolumeWorkerResponse &
            runDeleteLogicalVolumeWorker(const unsigned int id, const DeleteLogicalVolumeWorkerCommand &command);

            DisableIscsiTargetWorkerResponse &
            runDisableIscsiTargetWorker(const unsigned int id, const DisableIscsiTargetWorkerCommand &command);

            EnableIscsiTargetWorkerResponse &
            runEnableIscsiTargetWorker(const unsigned int id, const EnableIscsiTargetWorkerCommand &command);

        private:
            /**
             * @brief openWorkerFactory_ - фабрика объектов типа OpenWorker
             */
            OpenWorkerFactory openWorkerFactory_;
            /**
             * @brief closeWorkerFactory_- фабрика объектов типа CloseWorker
             */
            CloseWorkerFactory closeWorkerFactory_;
            /**
             * @brief createIscsiTargetWorkerFactory_ - фабрика объектов типа CreateIscsiTargetWorker
             */
            CreateIscsiTargetWorkerFactory createIscsiTargetWorkerFactory_;

            EnableIscsiTargetWorkerFactory enableIscsiTargetWorkerFactory_;

            ConnectDeviceToIscsiTargetWorkerFactory connectDeviceToIscsiTargetWorkerFactory_;
            /**
             * @brief removeIscsiTargetWorkerFactory_ - фабрика объектов типа RemoveIscsiTargetWorkerFactory
             */
            DisconnectDeviceToIscsiTargetWorkerFactory disconnectDeviceToIscsiTargetWorkerFactory_;
            /**
             * @brief disconnectDeviceToTargetWorkerFactory
             */
            RemoveIscsiTargetWorkerFactory removeIscsiTargetWorkerFactory_;
            /**
             * @brief - фабрика объектов типа CreateRaidWorker
             */
            CreateRaidWorkerFactory createRaidWorkerFactory_;
            /**
            * @brief - фабрика объектов типа DestroyRaidWorker
            */
            DestroyRaidWorkerFactory destroyRaidWorkerFactory_;
            /**
            * @brief - фабрика объектов типа DeleteLogicalVolumeWorker
            */
            DeleteLogicalVolumeWorkerFactory deleteLogicalVolumeWorkerFactory_;

            /**
             * @brief CreateLvmWorkerFactory_ - фабрика объектов типа CreateLvmWorker
             */
            CreateLvmWorkerFactory createLvmWorkerFactory_;
            /**
             * @brief - фабрика объектов типа DestroyLvmWorker
             */
            DestroyLvmWorkerFactory destroyLvmWorkerFactory_;

            DisableIscsiTargetWorkerFactory disableIscsiTargetWorkerFactory_;

        private:
            /**
             * @brief init - метод инциализации полей класса
             */
            void init();

        };

    }
}

