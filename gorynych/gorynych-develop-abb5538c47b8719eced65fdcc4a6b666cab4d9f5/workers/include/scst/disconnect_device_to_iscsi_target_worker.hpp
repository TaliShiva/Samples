#pragma once

#include "abstract_scst_worker.hpp"
#include "../commands/disconnect_device_to_iscsi_target_worker_command.hpp"
#include "../responses/disconnect_device_to_iscsi_worker_response.hpp"

namespace gorynych {
    namespace workers {
        class DisconnectDeviceToIscsiTargetWorker : public AbstractScstWorker {
        public:
            DisconnectDeviceToIscsiTargetWorker(const unsigned int id,
                                                const DisconnectDeviceToIscsiTargetWorkerCommand &command);


            DisconnectDeviceToIscsiTargetWorkerResponse &doWork() override;

            void sendNotification() override;

        private:
            const std::string generatePathForDisconnectDeviceToTargetCommand() const;
            const std::string generateStringForDisconnectDeviceToTargetCommand();


        protected:
            const std::string generateSystemErrorMessage();

            const std::string generateProgrammerErrorMessage();

            DisconnectDeviceToIscsiTargetWorkerCommand command_;


//            DisconnectDeviceToIscsiTargetWorkerCommand command;


        };
    }
}