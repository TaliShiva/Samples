#pragma once

#include "../abstract_worker.hpp"
#include "abstract_scst_worker.hpp"
#include "../commands/add_disk_to_scst_worker_command.hpp"
#include "../responses/add_disk_to_scst_worker_response.hpp"

namespace gorynych {
    namespace workers {
        class AddDiskToScstWorker : public AbstractScstWorker {
        public:
            AddDiskToScstWorker(const unsigned int id, const AddDiskToScstWorkerCommand &command);

            AddDiskToScstWorkerResponse &doWork() override;

            void sendNotification() override;

        private:
            AddDiskToScstWorkerCommand command_;

            /**
             * @brief generateStringForAddCommand() - генерирует строку,
             * которая будет записана в файл при выполнении
             * команды addDevice()
             * @return - сгенерированная строка
             */
            const std::string generateStringForAddCommand();

            /**
             * @brief generateSystemErrorMessage() - генерерирует сообщение о системной ошибке
             * @return сообщение об ошибке от системы: errno + description
             */
            const std::string generateSystemErrorMessage() override;

            /**
             * @brief generateProgrammerErrorMessage() - генерирует сообщение об ошибке от программиста
             * @return строка с сообщением
             */
            const std::string generateProgrammerErrorMessage() override;

        };


    }
}
