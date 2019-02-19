#include "../../../include/factories/scst/disconnect_device_to_iscsi_target_worker_factory.hpp"
#include "../../../../workers/include/scst/disconnect_device_to_iscsi_target_worker.hpp"
namespace gorynych{
    namespace worker_manager{

        AbstractWorker *DisconnectDeviceToIscsiTargetWorkerFactory::createWorker(const unsigned int id) {
            return new DisconnectDeviceToIscsiTargetWorker(id, *command_);
        }
    }
}
