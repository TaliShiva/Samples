//
// Created by user on 13.03.17.
//
#pragma once

#include "../abstract_worker.hpp"
#include "../responses/create_raid_worker_response.hpp"
#include "../commands/create_raid_worker_command.hpp"

namespace gorynych {
    namespace workers {
        class CreateRaidWorker: public AbstractWorker {
        public:

            CreateRaidWorker(const unsigned int id, CreateRaidWorkerCommand command);
            CreateRaidWorkerResponse &doWork();
            void sendNotification() override;
        private:

            CreateRaidWorkerCommand command_;
            /**
             * @return - возвращает строку с коммандой для создания raid-массива
             */
            std::string getMdadmCommand() const;
        };

    }
}