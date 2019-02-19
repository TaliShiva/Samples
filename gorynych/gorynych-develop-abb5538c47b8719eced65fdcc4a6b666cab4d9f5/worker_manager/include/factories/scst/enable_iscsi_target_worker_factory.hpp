#pragma once


#include "../abstact_worker_factory.hpp"
#include "../../../../workers/include/commands/enable_iscsi_target_worker_command.hpp"
#include "../../../../workers/include/scst/enable_iscsi_target_worker.hpp"

namespace gorynych {
    namespace worker_manager {

        class EnableIscsiTargetWorkerFactory : public AbstractWorkerFactory {
        public:
            EnableIscsiTargetWorkerFactory() {}

            AbstractWorker *createWorker(const unsigned int id) override {
                return new EnableIscsiTargetWorker(id, *command_);
            }

            void init(const EnableIscsiTargetWorkerCommand &command) {
                command_ = &command;
            }

        private:
            const EnableIscsiTargetWorkerCommand *command_;
        };

    }
}


