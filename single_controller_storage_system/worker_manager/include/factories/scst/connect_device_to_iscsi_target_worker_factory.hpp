#pragma once

#include "../../../../workers/include/responses/iworker_response.hpp"
#include "../abstact_worker_factory.hpp"

namespace gorynych{
    namespace worker_manager{
        using namespace workers;
        class ConnectDeviceToIscsiTargetWorkerFactory : public AbstractWorkerFactory{
        public:
            AbstractWorker *createWorker(const unsigned int id) override;
            void init(const ConnectDeviceToIscsiTargetWorkerCommand &command){
                command_ = &command;
            }

        private:
            const ConnectDeviceToIscsiTargetWorkerCommand *command_;
        };
    }
}