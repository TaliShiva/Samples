//
//

#pragma once

#include "../abstract_worker.hpp"
#include "../commands/delete_logical_volume_command.hpp"
#include "../responses/delete_logical_volume_worker_response.hpp"

namespace gorynych {
    namespace workers {

        /**
         * Worker удаляеи LVM Volume Group
         */
        class DeleteLogicalVolumeWorker : public AbstractWorker {
        public:
            DeleteLogicalVolumeWorker(const unsigned int id, const DeleteLogicalVolumeWorkerCommand &command);

            /**
             * @brief Запустить выполнение Worker'а
             * @return ответ воркера
             */
            DeleteLogicalVolumeWorkerResponse &doWork() override;

            void sendNotification() override;

        private:
            /**
             * Команда переданная Worker'у
             */
            DeleteLogicalVolumeWorkerCommand command_;
        };
    }
}

