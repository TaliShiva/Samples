
//

#pragma once

#include "../../../../workers/include/abstract_worker.hpp"
#include "../../worker_factory.hpp"
#include "../abstact_worker_factory.hpp"
#include "../../../../workers/include/lvm/create_lvm_worker.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        class CreateLvmWorkerFactory : public AbstractWorkerFactory {
        public:
            AbstractWorker *createWorker(const unsigned int id) override;

            void init(const CreateLvmWorkerCommand &command) { command_ = &command; }

        private:
            const CreateLvmWorkerCommand *command_;
        };
    }
}

