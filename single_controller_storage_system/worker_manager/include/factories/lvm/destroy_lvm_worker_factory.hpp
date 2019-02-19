
//

#pragma once

#include "../../../../workers/include/lvm/destroy_lvm_worker.hpp"
#include "../abstact_worker_factory.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        class DestroyLvmWorkerFactory : public AbstractWorkerFactory {
        public:
            AbstractWorker *createWorker(const unsigned int id) override;

            void init(const DestroyLvmWorkerCommand &command) { command_ = &command; }

        private:
            const DestroyLvmWorkerCommand *command_;
        };
    }
}


