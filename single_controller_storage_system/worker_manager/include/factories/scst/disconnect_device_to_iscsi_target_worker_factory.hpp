#pragma once

#include "../../../../workers/include/responses/iworker_response.hpp"
#include "../abstact_worker_factory.hpp"
#include "../../../../workers/include/commands/disconnect_device_to_iscsi_target_worker_command.hpp"
namespace gorynych{
    namespace worker_manager{
        using namespace workers;
        class DisconnectDeviceToIscsiTargetWorkerFactory : public AbstractWorkerFactory{
        public:
            AbstractWorker *createWorker(const unsigned int id) override;
            void init(const DisconnectDeviceToIscsiTargetWorkerCommand &command){
                command_ = &command;
            }

        private:
            const DisconnectDeviceToIscsiTargetWorkerCommand *command_;
        };
    }
}