//
// Created by dumplings on 14.03.17.
//
#pragma once

#include "abstract_scst_worker.hpp"
#include "../commands/create_target_worker_command.hpp"
#include "../responses/connect_device_to_iscsi_target_worker_response.hpp"

namespace gorynych{
    namespace workers{
        class ConnectDeviceToIscsiTargetWorker : public AbstractScstWorker{
        public:
            ConnectDeviceToIscsiTargetWorker (const unsigned int id, const ConnectDeviceToIscsiTargetWorkerCommand &command);

            ConnectDeviceToIscsiTargetWorkerResponse& doWork() override;

            void sendNotification() override;

        private:

            const std::string generatePathForConnectDeviceToTargetCommand() const;

            /**
             * @brief generateStringForConnectDeviceToTargetCommand()  - генерирует строку,
             * которая будет записана в файл при выполнении команды connectDeviceToTarget()
             * @return - сгенерированная строка
            */
            const std::string generateStringForConnectDeviceToTargetCommand();

        protected:
            const std::string generateSystemErrorMessage() override;

            const std::string generateProgrammerErrorMessage() override;

            ConnectDeviceToIscsiTargetWorkerCommand command_;


        };
    }
}
