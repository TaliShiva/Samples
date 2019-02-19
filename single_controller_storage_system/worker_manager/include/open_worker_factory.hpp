#pragma once

#include "worker_factory.hpp"


namespace gorynych {
    namespace worker_manager {
        /**
         * @class OpenWorkerFactory - фабрика объектов типа OpenWorker
         */
        class OpenWorkerFactory : public WorkerFactory {
        public:
            /**
             * @brief createWorker -  создает нового исполнителя
             * @param id - уникальный идентификатор
             * @return указатель на объект класса OpenWorker
             */
            AbstractWorkerOld *createWorker(const unsigned int id) override;
        };

    }
}