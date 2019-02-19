//
// Created by boa on 13.02.17.
//

#pragma once

#include "../../transport/include/response/text.hpp"
#include "../../transport/include/command.hpp"
#include "../../transport/include/transport_api.hpp"
#include "responses/iworker_response.hpp"
#include "responses/create_target_worker_response.hpp"

namespace gorynych {
    namespace workers {
        enum class WORKER_TYPE {
            ABSTRACT_WORKER,
            ABSTRACT_SCST_WORKER,
            CREATE_ISCSI_TARGET_WORKER,
            CREATE_CACHED_DISK_WORKER,
            DETACH_CACHED_DISK_WORKER,
            REMOVE_ISCSI_TARGET_WORKER,
            REMOVE_DISK_FROM_SCST_WORKER,
            CREATE_RAID_WORKER,
            CREATE_LVM_WORKER,
            DESTROY_LVM,
            DELETE_LOGICAL_VOLUME_WORKER,
            ADD_DISC_TO_SCST_WORKER,
            DESTROY_RAID_WORKER,
            CREATE_LOGICAL_VOLUME_WORKER,
            DISABLE_ISCSI_TARGET_WORKER,
            CONNECT_DEVICE_TO_ISCSI_TARGET_WORKER,
            DISCONNECT_DEVICE_TO_ISCSI_TARGET_WORKER,
            ENABLE_ISCSI_TARGET_WORKER,
        };

        using namespace transport;

        /**
         * @class AbstractWorker - базовый класс для всех исполнителей
         */
        class AbstractWorker {
        public:
            /**
             * @brief AbstractWorker - конструктор
             * @param id - уникальный идентификатор
             * @param workerType - тип исполнителя, на данный момент используется для внутренних нужд
             */
            AbstractWorker(const unsigned int id, const WORKER_TYPE workerType = WORKER_TYPE::ABSTRACT_WORKER)
                    : id_(id), workerType_(workerType) {}

            /**
             * @brief метод, с которого начинается работа исполнителя
             * @return @todo заменить на void, отправлять сигнал по завершении работы
             */
            virtual IWorkerResponse &doWork() = 0;
        public:
            /**
             * @brief метод отправки уведомлений об изменении глобальных состояний системы
             */
            virtual void sendNotification() = 0;

            virtual ~AbstractWorker() {

            }


        protected:
            const unsigned int id_;
            const WORKER_TYPE workerType_;
            /**
             * @brief lastSystemError_ - последняя системная ошибка
            */
            std::string lastSystemError_;

        };

    }
}




