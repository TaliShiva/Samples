//

#include <iostream>
#include "../../include/response/list_raid_response.hpp"
#include "../../include/struct/list/state_items.hpp"

namespace gorynych {
    namespace transport {

        ListRaidResponse::ListRaidResponse(const std::string &codedData)
                : AbstractResponse(codedData, ResponseType::LIST_RAID_RESPONSE,
                                   ProtoResponse::RESPONSE_LIST_RAID) {
//            std::cout << protobufMessage_.DebugString();
        }

        ListRaidResponse::ListRaidResponse()
                : AbstractResponse(ResponseType::LIST_RAID_RESPONSE,
                                   ProtoResponse::RESPONSE_LIST_RAID) {}

        int ListRaidResponse::listSize() const {
            return  protobufMessage_.list_raid().raid_item_size();
        }
        void ListRaidResponse::setRaidItemList(const RaidItemList &raidItemList) {
            for (auto item : raidItemList) {
                auto pointer = protobufMessage_.mutable_list_raid()->add_raid_item();
                pointer->set_raid_name(item.raidPath);
                pointer->set_raid_level(item.raidLevel);
                pointer->set_raid_size(item.raidSize);
                pointer->set_volume_group_name(item.volumeGroupName);
                pointer->set_volume_group_used_percentile(item.volumeGroupUsedPercentile);
                for (auto raidDevice : item.raidDevices) {
                    pointer->add_raid_devices(raidDevice);
                }
            }
        }

        const RaidItemList ListRaidResponse::raidItemList() const {
            RaidItemList itemList;
            itemList.reserve(listSize());
            for (auto raidItem : protobufMessage_.list_raid().raid_item()) {
                auto moveFromProto = [](protobuf::Response_Response_LIST_RAID_RAID raid) {
                    RaidItem result;
                    result.raidLevel = raid.raid_level();
                    result.raidPath = raid.raid_name();
                    result.raidSize = raid.raid_size();
                    result.volumeGroupName = raid.volume_group_name();
                    result.volumeGroupUsedPercentile = raid.volume_group_used_percentile();
                    for (auto device : raid.raid_devices()) {
                        result.raidDevices.emplace_back(device);
                    }
                    return result;
                };
                itemList.emplace_back(moveFromProto(raidItem));
            }
            return itemList;
        }
    }
}