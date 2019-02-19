//

#include "../../include/state/system_state.hpp"
#include "../../../transport/include/struct/list/state_items.hpp"
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
#include "../../../utils/include/start_custom_programm.hpp"
namespace gorynych {
    namespace logic {
        using namespace utils;
        void SystemState::addRaid(const std::string &raidPath, const std::string &raidLevel,
                                  const std::vector<std::string> raidDevices) {
            if (isRaidExists(raidPath)) {
                throw std::runtime_error("Raid " + raidPath + " already exists");
            }
            RaidItem item;
            item.raidPath = raidPath;
            item.raidLevel = raidLevel;
            item.raidSize = getRaidSize(raidPath);

            item.raidDevices = raidDevices;
            raidMap_.insert(std::make_pair(raidPath, item));
        }

        void SystemState::deleteRaid(const std::string &raidPath) {
            if (!isRaidExists(raidPath)) {
                throw std::runtime_error("Attempt to remove a nonexistent raid");
            }
            raidMap_.erase(raidPath);
        }

        void SystemState::setRaidVolumeGroup(const std::string &raidPath,
                                             const std::string &volumeGroupName) {
            auto it = raidMap_.find(raidPath);
            if (it == raidMap_.end()) {
                throw std::runtime_error("Attempt to change a nonexistent raid");
            }
            it->second.volumeGroupName = volumeGroupName;
            recalculateUsePercentage(volumeGroupName);
        }

        void SystemState::unsetRaidVolumeGroup(const std::string &raidPath) {
            auto it = raidMap_.find(raidPath);
            if (it == raidMap_.end()) {
                throw std::runtime_error(std::string("Attempt to change a nonexistent raid" + raidPath));
            }
            it->second.volumeGroupName = "";
            it->second.volumeGroupUsedPercentile = "";
        }

        void SystemState::addLogicalVolume(const std::string &logicalVolumeName,
                                           const std::string &volumeGroupName,
                                           const std::string &size) {
            if (isLogicalVolumeExists(logicalVolumeName, volumeGroupName)) {
                throw std::runtime_error(
                        std::string("Logical volume "
                                    + makeLogicalVolumeKey(logicalVolumeName, volumeGroupName) +
                                    " already exists"));
            }
            LogicalVolumeItem item;
            item.volumeGroupName = volumeGroupName;
            item.logicalVolumeName = logicalVolumeName;
            item.logicalVolumeSize = size;
            logicalVolumeMap_.insert(std::make_pair(makeLogicalVolumeKey(logicalVolumeName, volumeGroupName), item));
            recalculateUsePercentage(volumeGroupName);
        }

        void SystemState::deleteLogicalVolume(const std::string &logicalVolumeName,
                                              const std::string &volumeGroupName) {
            if (!isLogicalVolumeExists(logicalVolumeName, volumeGroupName)) {
                throw std::runtime_error(std::string("Attempt to delete a nonexistent logical volume " +
                                                         makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            }
            logicalVolumeMap_.erase(makeLogicalVolumeKey(logicalVolumeName, volumeGroupName));
            recalculateUsePercentage(volumeGroupName);
        }

        void SystemState::setVdiskName(const std::string &logicalVolumeName,
                                       const std::string &volumeGroupName,
                                       const std::string &vDiskName) {
            auto search = logicalVolumeMap_.find((makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            if (search == logicalVolumeMap_.end()) {
                throw std::runtime_error(std::string("Attempt to set vDiskName on a nonexistent logical volume " +
                                                         makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            }
            search->second.vDiskName = vDiskName;
        }

        void SystemState::setCache(const std::string &logicalVolumeName,
                                   const std::string &volumeGroupName,
                                   const std::string &cachingDevice) {
            auto search = logicalVolumeMap_.find((makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            if (search == logicalVolumeMap_.end()) {
                throw std::runtime_error(std::string("Attempt to set cache on a nonexistent logical volume " +
                                                         makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            }
            search->second.cachedDeviceName = cachingDevice;
            search->second.cached = true;
        }

        void SystemState::unsetVdiskName(const std::string &logicalVolumeName,
                                         const std::string &volumeGroupName) {
            auto search = logicalVolumeMap_.find((makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            if (search == logicalVolumeMap_.end()) {
                throw std::runtime_error(std::string("Attempt to unset vDiskName on a nonexistent logical volume " +
                                                         makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            }
            search->second.vDiskName = "";
        }

        void SystemState::unsetCache(const std::string &logicalVolumeName,
                                     const std::string &volumeGroupName) {
            auto search = logicalVolumeMap_.find((makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            if (search == logicalVolumeMap_.end()) {
                throw std::runtime_error(std::string("Attempt to unset cache on a nonexistent logical volume " +
                                                         makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            }
            search->second.cachedDeviceName = "";
            search->second.cached = false;
        }

        void SystemState::addLun(const std::string &targetName,
                                 const unsigned int lunNumber,
                                 const std::string &vDiskName) {
            if (!isTargetExists(targetName)) {
                throw std::runtime_error(
                        std::string("Attempt to access a nonexistent target with name " + targetName));
            }
            if (isLunInTargetExists(targetName, lunNumber)) {
                throw std::runtime_error(
                        std::string("Attempt to add duplicate LUN " + std::to_string(lunNumber)
                                    + " in target with name " + targetName));
            }
            LunItem item;
            item.lunNumber = lunNumber;
            item.vDiskName = vDiskName;
            targetMap_.find(targetName)->second.lunItems.emplace_back(item);
        }

        void SystemState::deleteLun(const std::string &targetName,
                                    const unsigned int lunNumber) {
            if (!isTargetExists(targetName)) {
                throw std::runtime_error(
                        std::string("Attempt to access a nonexistent target with name " + targetName));
            }
            auto lunList = targetMap_.find(targetName)->second.lunItems;
            auto it = std::find_if(lunList.begin(), lunList.end(),
                                [lunNumber](const LunItem &vectorItem) {
                                    return vectorItem.lunNumber == lunNumber;
                                });
            targetMap_.find(targetName)->second.lunItems.erase(it);
        }

        void SystemState::enableIscsiTarget(const std::string &targetName) {
            if (!isTargetExists(targetName)) {
                throw std::runtime_error(std::string("Attempt to enabled a nonexistent target"));
            }
            targetMap_.find(targetName)->second.enabled = true;
        }

        void SystemState::disableIscsiTarget(const std::string &targetName) {
            if (!isTargetExists(targetName)) {
                throw std::runtime_error(std::string("Attempt to disabled a nonexistent target"));
            }
            targetMap_.find(targetName)->second.enabled = false;
        }

        const RaidItemList SystemState::getRaidList() const {
            RaidItemList itemList;
            std::transform(raidMap_.begin(), raidMap_.end(),
                           std::back_inserter(itemList),
                           boost::bind(&RaidMap::value_type::second, _1));
            return itemList;
        }

        const LogicalVolumeItemList SystemState::getLogicalVolumeList() const {
            LogicalVolumeItemList itemList;
            std::transform(logicalVolumeMap_.begin(), logicalVolumeMap_.end(),
                           std::back_inserter(itemList),
                           boost::bind(&LogicalVolumeMap::value_type::second, _1));
            return itemList;
        }

        const TargetItemList SystemState::getTargetList() const {
            TargetItemList itemList;
            std::transform(targetMap_.begin(), targetMap_.end(),
                           std::back_inserter(itemList),
                           boost::bind(&TargetMap::value_type::second, _1));
            return itemList;
        }

        const std::string SystemState::makeLogicalVolumeKey(const std::string &logicalVolumeName,
                                                            const std::string &parentVolumeGroupName) const {
            return std::string(parentVolumeGroupName + "/" + logicalVolumeName);
        }

        bool SystemState::isRaidExists(const std::string &raidPath) {
            return raidMap_.count(raidPath) != 0;
        }

        bool SystemState::isLogicalVolumeExists(const std::string &logicalVolumeName,
                                                const std::string &parentVolumeGroupName) {
            return logicalVolumeMap_.count(makeLogicalVolumeKey(logicalVolumeName, parentVolumeGroupName)) != 0;
        }

        void SystemState::addIscsiTarget(const std::string &targetName) {
            if (isTargetExists(targetName)) {
                throw std::runtime_error(std::string("Target with name " + targetName  + " already exists"));
            }
            TargetItem item;
            item.targetName = targetName;
            targetMap_.insert(std::make_pair(targetName, item));
        }

        void SystemState::deleteIscsiTarget(const std::string &targetName) {
            if (!isTargetExists(targetName)) {
                throw std::runtime_error(std::string("Attempt to remove a nonexistent target with name " + targetName));
            }
            targetMap_.erase(targetName);
        }

        bool SystemState::isTargetExists(const std::string &targetName) const {
            return targetMap_.count(targetName) != 0;
        }

        bool SystemState::isTargetEnabled(const std::string &targetName) const {
            if (!isTargetExists(targetName)) {
                throw std::runtime_error("Attempt to access a nonexistent target with name " + targetName);
            }
            return targetMap_.find(targetName)->second.enabled;
        }

        bool SystemState::isLunInTargetExists(const std::string &targetName, const unsigned int lunNumber) {
            if (!isTargetExists(targetName)) {
                throw std::runtime_error("Attempt to access a nonexistent target with name " + targetName);
            }
            auto lunList = targetMap_.find(targetName)->second.lunItems;
            return std::find_if(lunList.begin(), lunList.end(),
                                [lunNumber](const LunItem &vectorItem) {
                                    return vectorItem.lunNumber == lunNumber;
                                }) != lunList.end();
        }

        std::string SystemState::getRaidSize(const std::string &raidPath) {
            std::string out;
            if (startCustomProgramm("mdadm -Y " + raidPath, out) != 0) {
                return "unknown size";
            }
            using namespace boost::algorithm;
            std::vector<std::string> split_output;
            const int splitCount = 2;
            split(split_output, out, is_any_of(" "));
            if (split_output.size() >= splitCount) {
                return split_output.at(1);
            }
            return "unknown size";
        }

        bool SystemState::isCached(const std::string &logicalVolumeName, const std::string &volumeGroupName) {
            auto search = logicalVolumeMap_.find((makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            if (search == logicalVolumeMap_.end()) {
                throw std::runtime_error(std::string("Attempt to check cache on a nonexistent logical volume " +
                                                         makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            }
            return search->second.cached;
        }

        const std::string
        SystemState::getCachingDevicePath(const std::string &logicalVolumeName, const std::string &volumeGroupName) {
            auto search = logicalVolumeMap_.find((makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            if (search == logicalVolumeMap_.end()) {
                throw std::runtime_error(std::string("Attempt to check cache on a nonexistent logical volume " +
                                                         makeLogicalVolumeKey(logicalVolumeName, volumeGroupName)));
            }
            return search->second.cached ? search->second.cachedDeviceName : "";
        }

        const std::string SystemState::getUsePercentage(const std::string &volumeGroupName) {
            std::string allExtentsCount;
            std::string freeExtentsCount;
            const std::string freeExtentsCmd = "vgs --noheadings --ignorelockingfailure --ignoreskippedcluster -o vg_free_count " + volumeGroupName;
            const std::string allExtentsCmd = "vgs --noheadings --ignorelockingfailure --ignoreskippedcluster -o vg_extent_count " + volumeGroupName;
            if ((startCustomProgrammWithoutErrorOut(allExtentsCmd, allExtentsCount) != 0) || (startCustomProgrammWithoutErrorOut(freeExtentsCmd,freeExtentsCount) != 0)) {
                return "unknown %";
            }
            try {
                auto all = std::stod(allExtentsCount);
                auto free = std::stod(freeExtentsCount);
                return std::to_string((int)(100 - (free / all) * 100)) + " %";
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
                return "unknown %";
            }
        }

        void SystemState::recalculateUsePercentage(const std::string &volumeGroup) {
            for (auto &raidItem : raidMap_) {
                if (raidItem.second.volumeGroupName == volumeGroup) {
                    raidItem.second.volumeGroupUsedPercentile = getUsePercentage(volumeGroup);
                }
            }
        }

        const StringVector SystemState::getRaidDevices(const std::string &raidPath) const {
            auto it = raidMap_.find(raidPath);
            if (it == raidMap_.end()) {
                throw std::runtime_error(std::string("Attempt to access a nonexistent raid"));
            }
            return it->second.raidDevices;
        }
    }
}