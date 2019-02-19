//

#include "../../include/response/list_scst_response.hpp"

namespace gorynych {
    namespace transport {
        ListScstResponse::ListScstResponse(const std::string &codedData)
                : AbstractResponse(codedData, ResponseType::LIST_SCST_RESPONSE,
                                   ProtoResponse::RESPONSE_LIST_SCST) {
            std::cout << protobufMessage_.DebugString();
        }

        ListScstResponse::ListScstResponse()
                : AbstractResponse(ResponseType::LIST_SCST_RESPONSE,
                                   ProtoResponse::RESPONSE_LIST_SCST) {}

        void ListScstResponse::setTargetItemList(const TargetItemList &targetItemList) {
            for (auto item : targetItemList) {
                auto targetPointer = protobufMessage_.mutable_list_scst()->add_target_item();
                targetPointer->set_target_name(item.targetName);
                targetPointer->set_enabled(item.enabled);
                for (auto lunItem : item.lunItems) {
                    auto lunPointer = targetPointer->add_lun_item();
                    lunPointer->set_lun_number(lunItem.lunNumber);
                    lunPointer->set_vdisk_name(lunItem.vDiskName);
                }
            }
        }

        const TargetItemList ListScstResponse::targetItemList() const {
            TargetItemList targetItemList;
            for (auto targetItem : protobufMessage_.list_scst().target_item()) {
                auto moveTargetFromProto = [] (protobuf::Response_Response_LIST_SCST_TARGET target) {
                    TargetItem result;
                    result.targetName = target.target_name();
                    result.enabled = target.enabled();
                    auto moveLunFromProto = [] (protobuf::Response_Response_LIST_SCST_TARGET_LUN lun) {
                        LunItem lunResult;
                        lunResult.lunNumber = lun.lun_number();
                        lunResult.vDiskName = lun.vdisk_name();
                        return lunResult;
                    };
                    for (auto lunItem : target.lun_item()) {
                        result.lunItems.emplace_back(moveLunFromProto(lunItem));
                    }
                    return result;
                };
                targetItemList.emplace_back(moveTargetFromProto(targetItem));
            }
            return targetItemList;
        }
    }
}
