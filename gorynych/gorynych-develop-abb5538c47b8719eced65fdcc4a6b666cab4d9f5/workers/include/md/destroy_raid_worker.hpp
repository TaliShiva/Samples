//
// Created by user on 15.03.17.
//

#pragma once

#include "../abstract_worker.hpp"
#include "../commands/destroy_raid_worker_command.hpp"
#include "../responses/destroy_raid_worker_response.hpp"

namespace gorynych {
    namespace workers {

        class DestroyRaidWorker : public AbstractWorker {
        public:
            /**
             * @param id - id worker-а
             * @param command - комманда с параметрами для удаления raid-массива
             */
            DestroyRaidWorker(const unsigned int id, const DestroyRaidWorkerCommand command);
            DestroyRaidWorkerResponse &doWork() override;
            void sendNotification() override;

        private:
            DestroyRaidWorkerCommand command_;
        };


    }
}