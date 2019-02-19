//
// Created by alex on 3/13/17.
//

#pragma once

#include "../abstract_worker.hpp"
#include "../commands/create_lvm_worker_command.hpp"
#include "../responses/create_lvm_worker_response.hpp"

namespace gorynych {
    namespace workers {

        /**
         * Worker создает на устройстве LVM Volume Group
         */
        class CreateLvmWorker : public AbstractWorker {
        public:
            CreateLvmWorker(const unsigned int id, const CreateLvmWorkerCommand &command);

            /**
             * @brief Запустить выполнение Worker'а
             * @return ответ воркера
             */
            CreateLvmWorkerResponse &doWork() override;

            void sendNotification() override;

        private:
            /**
             * Команда переданная Worker'у
             */
            CreateLvmWorkerCommand command_;
        };
    }
}



