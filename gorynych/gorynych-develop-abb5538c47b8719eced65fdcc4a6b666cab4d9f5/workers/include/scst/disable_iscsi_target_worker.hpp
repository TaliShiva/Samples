//

#pragma once

#include "../abstract_worker.hpp"
#include "abstract_scst_worker.hpp"
#include "../commands/disable_iscsi_target_worker_command.hpp"
#include "../responses/disable_iscsi_target_worker_response.hpp"

namespace gorynych {
    namespace workers {
        class DisableIscsiTargetWorker : public AbstractScstWorker {
        public:
            DisableIscsiTargetWorker(const unsigned int id, const DisableIscsiTargetWorkerCommand &command);

            DisableIscsiTargetWorkerResponse &doWork();

        private:
            DisableIscsiTargetWorkerCommand command_;
        public:
            void sendNotification() override;

        protected:
            const std::string generateSystemErrorMessage() override;

            const std::string generateProgrammerErrorMessage() override;
            /**
             * @brief generatePathForEnableTargetCommand() генерирует строку,
             * содержащую путь к  файлу, в который будет произведена запись  при выполнении
             * команды enableTarget()
             * @return - сгенерированная строка
             */
            const std::string generatePathForDisableTargetCommand() const;

        };
    }
}



