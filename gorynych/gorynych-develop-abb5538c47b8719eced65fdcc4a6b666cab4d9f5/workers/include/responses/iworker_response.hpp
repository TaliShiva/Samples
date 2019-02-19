#pragma once

namespace gorynych {
    namespace workers {
        enum class WorkerResponseType {
            CREATE_TARGET,
            ENABLE_ISCSI_TARGET,
            CREATE_RAID,
            DESTROY_RAID,
            ADD_DISK_TO_SCST,
            REMOVE_TARGET,
            REMOVE_DISK_FROM_SCST,
            CREATE_LVM,
            DESTROY_LVM,
            CREATE_LOGICAL_VOLUME,
            DELETE_LOGICAL_VOLUME,
            CONNECT_DEVICE_TO_ISCSI_TARGET,
            DISABLE_ISCSI_TARGET,
            DISCONNECT_DEVICE_TO_ISCSI_TARGET,
        };

        class IWorkerResponse {
        protected:

        };

    }
}


