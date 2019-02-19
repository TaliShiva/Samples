#include "../include/close_worker_factory.hpp"
#include "../../workers/include/close_worker.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        AbstractWorkerOld *CloseWorkerFactory::createWorker(const unsigned int id) {
            return new CloseWorker(id);
        }
    }
}

