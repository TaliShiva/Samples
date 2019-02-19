#pragma once

#include "worker_factory.hpp"


namespace gorynych {
    namespace worker_manager {
        /**
         * @class CloseWorkerFactory - фабрика объектов типа CloseWorker
         */
        class CloseWorkerFactory : public WorkerFactory {
        public:
            /**
                        * @brief createWorker -  создает нового исполнителя
                        * @param id - уникальный идентификатор
                        * @return указатель на объект класса CloseWorker
                        */
            virtual AbstractWorkerOld *createWorker(const unsigned int id) override;
        };
    }
}
