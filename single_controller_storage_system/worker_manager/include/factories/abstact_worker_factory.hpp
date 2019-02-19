#pragma once


#include "../../../workers/include/abstract_worker.hpp"
#include "../../../workers/include/scst/create_iscsi_target_worker.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        class AbstractWorkerFactory {
        public:
            /**
             * @brief createWorker -  создает нового исполнителя, чисто виртуальный метод
             * @param id - уникальный идентификатор
             * @return указатель на объект класса AbstractWorker
             */
            virtual AbstractWorker *createWorker(const unsigned int id) = 0;
        };
    }
}
