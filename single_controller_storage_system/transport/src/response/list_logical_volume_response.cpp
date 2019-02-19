//

#include "../../include/response/list_logical_volume_response.hpp"
#include "../../include/struct/list/state_items.hpp"

namespace gorynych {
    namespace transport {

        ListLogicalVolumeResponse::ListLogicalVolumeResponse(const std::string &codedData)
                : AbstractResponse(codedData, ResponseType::LIST_LOGICAL_VOLUME_RESPONSE,
                                   ProtoResponse::RESPONSE_LIST_LOGICAL_VOLUME) {

        }

        ListLogicalVolumeResponse::ListLogicalVolumeResponse()
                : AbstractResponse(ResponseType::LIST_LOGICAL_VOLUME_RESPONSE,
                                   ProtoResponse::RESPONSE_LIST_LOGICAL_VOLUME) {}

        int ListLogicalVolumeResponse::listSize() const {
            return  protobufMessage_.list_logical_volume().logical_volume_item_size();
        }
        void ListLogicalVolumeResponse::setLogicalVolumeItemList(const LogicalVolumeItemList &itemList) {
            for (auto item : itemList) {
                auto pointer = protobufMessage_.mutable_list_logical_volume()->add_logical_volume_item();
                pointer->set_logical_volume_name(item.logicalVolumeName);
                pointer->set_logical_volume_size(item.logicalVolumeSize);
                pointer->set_volume_group_name(item.volumeGroupName);
                pointer->set_vdisk_name(item.vDiskName);
                pointer->set_cached(item.cached);
                pointer->set_cached_device_name(item.cachedDeviceName);
            }
        }

        const LogicalVolumeItemList ListLogicalVolumeResponse::logicalVolumeItemList() const {
            LogicalVolumeItemList itemList;
            itemList.reserve(listSize());
            for (auto item : protobufMessage_.list_logical_volume().logical_volume_item()) {
                auto moveFromProto = [](protobuf::Response_Response_LIST_LOGICAL_VOLUME_LOGICAL_VOLUME lvItem) {
                    LogicalVolumeItem result;
                    result.logicalVolumeName = lvItem.logical_volume_name();
                    result.logicalVolumeSize = lvItem.logical_volume_size();
                    result.volumeGroupName = lvItem.volume_group_name();
                    result.vDiskName = lvItem.vdisk_name();
                    result.cached = lvItem.cached();
                    result.cachedDeviceName = lvItem.cached_device_name();
                    return result;
                };
                itemList.emplace_back(moveFromProto(item));
            }
            return itemList;
        }
    }
}