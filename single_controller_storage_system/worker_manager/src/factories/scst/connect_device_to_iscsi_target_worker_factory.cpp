//
// Created by dumplings on 15.03.17.
//

#include "../../../include/factories/scst/connect_device_to_iscsi_target_worker_factory.hpp"
#include "../../../../workers/include/scst/connect_device_to_iscsi_target_worker.hpp"

namespace gorynych{
    namespace worker_manager{
        using namespace workers;

        AbstractWorker *ConnectDeviceToIscsiTargetWorkerFactory::createWorker(const unsigned int id) {
            return new ConnectDeviceToIscsiTargetWorker(id,*command_);
        }
    }
}