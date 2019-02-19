
#include "../../../include/factories/lvm/delete_logical_volume_worker_factory.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        AbstractWorker *
        DeleteLogicalVolumeWorkerFactory::createWorker(const unsigned int id) {
            return new DeleteLogicalVolumeWorker(id, *command_);
        }
    }
}