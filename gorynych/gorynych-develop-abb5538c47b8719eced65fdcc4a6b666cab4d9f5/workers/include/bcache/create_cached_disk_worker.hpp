#pragma once

#include "../abstract_worker.hpp"
#include "../responses/silent_worker_response.hpp"
#include "../commands/create_cached_disk_worker_command.hpp"

namespace gorynych {
    namespace workers {

        class CreateCachedDiskWorker {
        public:
            CreateCachedDiskWorker(const unsigned int id, const CreateCachedDiskWorkerCommand &command);
            ~CreateCachedDiskWorker() = default;
            SilentWorkerResponse *doWork();
        private:
            CreateCachedDiskWorkerCommand command_;
        };
    }
}