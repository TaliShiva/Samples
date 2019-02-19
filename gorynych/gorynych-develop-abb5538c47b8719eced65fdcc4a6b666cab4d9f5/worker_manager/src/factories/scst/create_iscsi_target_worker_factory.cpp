#include "../../../include/factories/scst/create_iscsi_target_worker_factory.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        AbstractWorker *
        CreateIscsiTargetWorkerFactory::createWorker(const unsigned int id) {
            return new CreateIscsiTargetWorker(id, *command_);
        }
    }
}
