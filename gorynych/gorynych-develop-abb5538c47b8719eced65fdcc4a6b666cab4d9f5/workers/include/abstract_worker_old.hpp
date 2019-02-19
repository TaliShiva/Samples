#pragma once

#include "../../transport/include/response/text.hpp"
#include "../../transport/include/command.hpp"
#include "../../transport/include/transport_api.hpp"
#include "responses/iworker_response.hpp"

namespace gorynych {
    namespace workers {
        enum class WORKER_TYPE_OLD {
            ABSTRACT_WORKER,
            OPEN_WORKER,
            CLOSE_WORKER
        };

        using namespace transport;

        /**
         * @class AbstractWorker - базовый класс для всех исполнителей
         */
        class AbstractWorkerOld {
        public:
            /**
             * @brief AbstractWorker - конструктор
             * @param id - уникальный идентификатор
             * @param workerType - тип исполнителя, на данный момент используется для внутренних нужд
             */
            AbstractWorkerOld(const unsigned int id,
                              const WORKER_TYPE_OLD workerType = WORKER_TYPE_OLD::ABSTRACT_WORKER)
                    : id_(id), workerType_(workerType) {}

            /**
             * @brief метод, с которого начинается работа исполнителя
             * @return @todo заменить на void, отправлять сигнал по завершении работы
             */
            virtual IResponse &doWork() = 0;

//            virtual void init(const ICommand &command) = 0;
        public:
            /**
             * @brief метод отправки уведомлений об изменении глобальных состояний системы
             */
            virtual void sendNotification() = 0;


        protected:
            const unsigned int id_;
            const WORKER_TYPE_OLD workerType_;
            /**
             * @brief lastError_ - последняя системная ошибка
            */
            std::string lastError_;

        };

    }
}




