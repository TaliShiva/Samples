#pragma once

#include "abstract_scst_worker.hpp"
#include "../responses/create_target_worker_response.hpp"
#include "../commands/create_target_worker_command.hpp"

namespace gorynych {
    namespace workers {
        class CreateIscsiTargetWorker : public AbstractScstWorker {

        public:
            /**
             *
             * @param id
             * @param command
             */
            CreateIscsiTargetWorker(const unsigned int id, const CreateTargetWorkerCommand &command);
            /**
             * @brief doWork() - выполняет набор операций для создания ISCSI target
             * @return статус выполнения операции и служебные сообщения @see CreateTargetWorkerResponse
             */
            CreateTargetWorkerResponse &doWork();

            void sendNotification() override;

        private:
            /**
             * @brief generateStringForCreateTargetCommand - служебная команда, для генерации магичеких строк
             * @return магическая строка, записав которую в не менее магический файл мы получим нужный результат
             */
            const std::string generateStringForCreateTargetCommand();

            CreateTargetWorkerCommand command_;
        protected:
            const std::string generateSystemErrorMessage() override;

            const std::string generateProgrammerErrorMessage() override;
//            CreateTargetWorkerResponse response_;
        };
    }
}
