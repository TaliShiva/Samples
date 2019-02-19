#pragma once
#include "../../../../workers/include/abstract_worker.hpp"
#include "../../worker_factory.hpp"
#include "../abstact_worker_factory.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;
        /**
         * @class CreateIscsiTargetWorkerFactory @see documentation  AbstractWorkerFactory, mark as 
         */
        class CreateIscsiTargetWorkerFactory : public AbstractWorkerFactory {
        public:
            AbstractWorker *createWorker(const unsigned int id) override;

            void init(const CreateTargetWorkerCommand &command) { command_ = &command; }

        private:
            const CreateTargetWorkerCommand *command_;
        };
    }
}
