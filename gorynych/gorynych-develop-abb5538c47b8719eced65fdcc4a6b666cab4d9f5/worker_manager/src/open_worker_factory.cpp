#include "../include/open_worker_factory.hpp"


namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        AbstractWorkerOld *OpenWorkerFactory::createWorker(const unsigned int id) {
            return new OpenWorker(id);
        }
    }
}

