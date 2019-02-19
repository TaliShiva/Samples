//

#pragma once

#include "../transport_api.hpp"
#include "../struct/list/state_items.hpp"

namespace gorynych {
    namespace transport {
        /**
         * @class ListTargetResponse - хранит список SCST таргетов с подключенными лунами и vdisk'ами
         */
        class ListScstResponse :public AbstractResponse {
        public:

            ListScstResponse(const std::string &codedData);

            ListScstResponse();

            void setTargetItemList(const TargetItemList &targetItemList);

            const TargetItemList targetItemList() const;

        };

    }
}

