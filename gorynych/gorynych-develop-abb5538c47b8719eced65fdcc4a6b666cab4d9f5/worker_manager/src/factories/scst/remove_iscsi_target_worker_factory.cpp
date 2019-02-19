//
// Created by boa on 13.03.17.
//

#include "../../../include/factories/scst/remove_iscsi_target_worker_factory.hpp"
#include "../../../../workers/include/scst/remove_iscsi_target_worker.hpp"
namespace gorynych{
    namespace worker_manager{

        AbstractWorker *RemoveIscsiTargetWorkerFactory::createWorker(const unsigned int id) {
            return new RemoveIscsiTargetWorker(id,*command_);
        }
        void RemoveIscsiTargetWorkerFactory::init(const RemoveIscsiTargetWorkerCommand &command) {
            command_ = &command;
        }
    }
}
