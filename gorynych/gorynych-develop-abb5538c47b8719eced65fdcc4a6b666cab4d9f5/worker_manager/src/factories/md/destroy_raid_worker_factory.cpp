//
// Created by user on 15.03.17.
//

#include "../../../include/factories/md/destroy_raid_worker_factory.hpp"

namespace gorynych {
    namespace worker_manager {
        using namespace workers;

        AbstractWorker *
        DestroyRaidWorkerFactory::createWorker(const unsigned int id) {
            return new DestroyRaidWorker(id, *command_);
        }
    }
}