
//

#include "../../../include/factories/lvm/destroy_lvm_worker_factory.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        AbstractWorker *
        DestroyLvmWorkerFactory::createWorker(const unsigned int id) {
            return new DestroyLvmWorker(id, *command_);
        }
    }
}