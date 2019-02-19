//
// Created by user on 14.03.17.
//

#pragma once

#include "../../../../workers/include/abstract_worker.hpp"
#include "../../worker_factory.hpp"
#include "../abstact_worker_factory.hpp"
#include "../../../../workers/include/md/create_raid_worker.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;
        /**
        * @brief - создание raid-массива
        */
        class CreateRaidWorkerFactory : public AbstractWorkerFactory {
        public:
            AbstractWorker *createWorker(const unsigned int id) override;

            void init(const CreateRaidWorkerCommand &command) { command_ = &command; }

        private:
            const CreateRaidWorkerCommand *command_;
        };
    }
}
