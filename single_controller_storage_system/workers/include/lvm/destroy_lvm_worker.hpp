
//

#pragma once

#include "../scst/abstract_scst_worker.hpp"
#include "../responses/destroy_lvm_worker_response.hpp"
#include "../commands/destroy_lvm_worker_command.hpp"

namespace gorynych {
    namespace workers {
        /**
         * Worker уничтожает на устройстве LVM Volume Group
         */
        class DestroyLvmWorker : public AbstractWorker{
        public:
            DestroyLvmWorker(const unsigned int id, const DestroyLvmWorkerCommand &command);

            /**
             * @brief Запустить выполнение Worker'а
             * @return ответ воркера
             */
            DestroyLvmWorkerResponse &doWork() override;

            void sendNotification() override;

        private:
            /**
             * Команда переданная Worker'у
             */
            DestroyLvmWorkerCommand command_;
        };
    }
}



