//

#pragma once

#include "../abstact_worker_factory.hpp"
#include "../../../../workers/include/commands/disable_iscsi_target_worker_command.hpp"
#include "../../../../workers/include/scst/disable_iscsi_target_worker.hpp"
namespace gorynych {
    namespace worker_manager {
        class  DisableIscsiTargetWorkerFactory : public  AbstractWorkerFactory{


        public:
            DisableIscsiTargetWorkerFactory() {}
            AbstractWorker *createWorker(const unsigned int id) override {
                return new DisableIscsiTargetWorker(id, *command_);
            }
            void init(const DisableIscsiTargetWorkerCommand &command){ command_ = &command; }
        private:
            const DisableIscsiTargetWorkerCommand *command_;

        };

    }
}
