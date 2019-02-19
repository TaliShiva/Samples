
//

#include "../../../include/factories/lvm/create_lvm_worker_factory.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        AbstractWorker *
        CreateLvmWorkerFactory::createWorker(const unsigned int id) {
            return new CreateLvmWorker(id, *command_);
        }
    }
}