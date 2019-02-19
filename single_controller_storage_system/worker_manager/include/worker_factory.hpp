#pragma once

#include "../../workers/include/abstract_worker.hpp"
#include "../../workers/include/open_worker.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        /**
         * @class WorkerFactory - абстрактная фабрика исполнителей
         */
        class WorkerFactory {
        public:
            /**
             * @brief createWorker -  создает нового исполнителя, чисто виртуальный метод
             * @param id - уникальный идентификатор
             * @return указатель на объект класса AbstractWorker
             */
            virtual AbstractWorkerOld *createWorker(const unsigned int id) = 0;
        };
    }
}
