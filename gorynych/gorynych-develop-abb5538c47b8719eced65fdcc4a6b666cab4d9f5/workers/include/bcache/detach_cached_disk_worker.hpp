#pragma once

#include "../abstract_worker.hpp"
#include "../responses/silent_worker_response.hpp"
#include "../commands/detach_cached_disk_worker_command.hpp"

namespace gorynych {
    namespace workers {

        class DetachCachedDiskWorker {
        public:
            DetachCachedDiskWorker(const unsigned int id, const DetachCachedDiskWorkerCommand &command);
            ~DetachCachedDiskWorker() = default;
            SilentWorkerResponse *doWork();
        private:
            DetachCachedDiskWorkerCommand command_;
        };
    }
}