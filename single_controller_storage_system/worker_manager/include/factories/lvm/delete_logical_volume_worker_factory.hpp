
#pragma once

#include "../../../../workers/include/abstract_worker.hpp"
#include "../../worker_factory.hpp"
#include "../abstact_worker_factory.hpp"
#include "../../../../workers/include/lvm/delete_logical_volume_worker.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        class DeleteLogicalVolumeWorkerFactory : public AbstractWorkerFactory {
        public:
            AbstractWorker *createWorker(const unsigned int id) override;

            void init(const DeleteLogicalVolumeWorkerCommand &command) { command_ = &command; }

        private:
            const DeleteLogicalVolumeWorkerCommand *command_;
        };
    }

};



