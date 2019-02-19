//
// Created by user on 15.03.17.
//


#pragma once

#include "../../../../workers/include/abstract_worker.hpp"
#include "../../worker_factory.hpp"
#include "../abstact_worker_factory.hpp"
#include "../../../../workers/include/md/destroy_raid_worker.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;
        /**
         * @brief - удаление raid-массива
         */
        class DestroyRaidWorkerFactory : public AbstractWorkerFactory {
        public:
            AbstractWorker *createWorker(const unsigned int id) override;

            void init(const DestroyRaidWorkerCommand &command) { command_ = &command; }

        private:
            const DestroyRaidWorkerCommand *command_;
        };
    }
}
