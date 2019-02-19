//

#pragma once

#include "../transport_api.hpp"
#include "../struct/list/state_items.hpp"

namespace gorynych {
    namespace transport {
        /**
         * @class ListLogicalVolumeResponse - хранит список логических дисков LVM, сопоставленные им vdisk имена
         * из SCST, состояние кэша и путь к кэширующему устройству
         */
        class ListLogicalVolumeResponse : public AbstractResponse {
        public:
            ListLogicalVolumeResponse(const std::string &codedData);

            ListLogicalVolumeResponse();

            void setLogicalVolumeItemList(const LogicalVolumeItemList &itemList);

            const LogicalVolumeItemList logicalVolumeItemList() const;

            int listSize() const;

        };

    }
}

