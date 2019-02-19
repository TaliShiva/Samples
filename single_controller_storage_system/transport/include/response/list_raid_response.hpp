//

#pragma once

#include "../response.hpp"
#include "abstract_response.hpp"
#include "../struct/list/state_items.hpp"

namespace gorynych {
    namespace transport {
        /**
         * @class ListRaidResponse - хранит информацию о созданных RAID-массивах, ассоциированные с ними имено
         * volume group (LVM) и процент использования
         */
        class ListRaidResponse :public AbstractResponse {
        public:
            ListRaidResponse(const std::string &codedData);

            ListRaidResponse();

            void setRaidItemList(const RaidItemList &raidItemList);

            const RaidItemList raidItemList() const;

            int listSize() const;

        };

    }
}

