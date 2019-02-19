#include "../../../include/factories/md/create_raid_worker_factory.hpp"


namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        AbstractWorker *
        CreateRaidWorkerFactory::createWorker(const unsigned int id) {
            return new CreateRaidWorker(id, *command_);
        }
    }
}
