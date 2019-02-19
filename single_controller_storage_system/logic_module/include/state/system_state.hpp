//

#pragma once

#include <map>
#include "../../../transport/include/struct/list/state_items.hpp"
namespace gorynych {
    namespace logic {
        class SystemState {
        private:


        public:
            SystemState() {}

            SystemState &operator=(const SystemState &other) = delete;

            SystemState(const SystemState &other) = delete;



            /**
             * @brief
             * @param raidPath
             * @param raidLevel
             * @param raidDevices
             * @throws
             */
            void addRaid(const std::string &raidPath, const std::string &raidLevel,
                         const std::vector<std::string> raidDevices);

            /**
             * @brief
             * @param raidPath
             * @throws
             */
            void deleteRaid(const std::string &raidPath);

            /**
             * @brief
             * @param raidPath
             * @param volumeGroupName
             * @throws
             */
            void setRaidVolumeGroup(const std::string &raidPath,
                                    const std::string &volumeGroupName);

            /**
             * @brief
             * @param raidPath
             * @throws
             */
            void unsetRaidVolumeGroup(const std::string &raidPath);

            /**
             * @brief
             * @param raidPath
             * @return
             */
            bool isRaidExists(const std::string &raidPath);

            const std::string getUsePercentage(const std::string &volumeGroupName);

            /**
             * @brief
             * @param logicalVolumeName
             * @param size
             * @param volumeGroupName
             * @throws
             */
            void addLogicalVolume(const std::string &logicalVolumeName,
                                  const std::string &volumeGroupName,
                                  const std::string &size);



            /**
             * @brief
             * @param logicalVolumeName
             * @param volumeGroupName
             * @throws
             */
            void deleteLogicalVolume(const std::string &logicalVolumeName,
                                     const std::string &volumeGroupName);
            /**
             * @brief
             * @param logicalVolumeName
             * @param volumeGroupName
             * @param vDiskName
             * @throws
             */
            void setVdiskName(const std::string &logicalVolumeName,
                              const std::string &volumeGroupName,
                              const std::string &vDiskName);
            /**
             * @brief
             * @param logicalVolumeName
             * @param volumeGroupName
             * @throws
             */
            void unsetVdiskName(const std::string &logicalVolumeName,
                                const std::string &volumeGroupName);

            /**
             * @brief
             * @param logicalVolumeName
             * @param volumeGroupName
             * @param cachingDevice
             * @throws
             */
            void setCache(const std::string &logicalVolumeName,
                          const std::string &volumeGroupName,
                          const std::string &cachingDevice);

            /**
             * @brief
             * @param logicalVolumeName
             * @param volumeGroupName
             * @throws
             */
            void unsetCache(const std::string &logicalVolumeName,
                            const std::string &volumeGroupName);

            /**
             * @brief
             * @param logicalVolumeName
             * @param volumeGroupName
             * @return
             */
            bool isCached(const std::string &logicalVolumeName,
                          const std::string &volumeGroupName);

            const std::string getCachingDevicePath(const std::string &logicalVolumeName,
                                                   const std::string &volumeGroupName);

            /**
             * @brief
             * @param logicalVolumeName
             * @param parentVolumeGroupName
             * @return
             * @throws
             */
            bool isLogicalVolumeExists(const std::string &logicalVolumeName,
                                       const std::string &parentVolumeGroupName);

            /**
             * @brief
             * @param targetName
             * @throws
             */
            void addIscsiTarget(const std::string &targetName);

            /**
             * @brief
             * @param targetName
             * @throws
             */
            void deleteIscsiTarget(const std::string &targetName);

            /**
             * @brief
             * @param targetName
             * @param lunNumber
             * @param vDiskName
             * @throws
             */
            void addLun(const std::string &targetName,
                        const unsigned int lunNumber,
                        const std::string &vDiskName);

            /**
             * @brief
             * @param targetName
             * @param lunNumber
             * @throws
             */
            void deleteLun(const std::string &targetName,
                           const unsigned int lunNumber);

            /**
             * @brief
             * @param targetName
             * @throws
             */
            void enableIscsiTarget(const std::string &targetName);

            /**
             * @brief
             * @param targetName
             * @throws
             */
            void disableIscsiTarget(const std::string &targetName);

            /**
             * @brief
             * @param targetName
             * @return
             */
            bool isTargetExists(const std::string &targetName) const;

            /**
             * @brief getRaidList
             * @return
             * @throws
             */
            const RaidItemList getRaidList() const;

            /**
             *
             * @param raidPath
             * @return
             */
            const StringVector getRaidDevices(const std::string &raidPath) const;

            /**
             * @brief getLogicalVolumeList
             * @return
             * @throws
             */
            const LogicalVolumeItemList getLogicalVolumeList() const;

            /**
             * @brief getTargetList
             * @return
             * @throws
             */
            const TargetItemList getTargetList() const;

            /**
             *
             * @param targetName
             * @return
             */
            bool isTargetEnabled(const std::string &targetName) const;
        private:
            typedef std::map<std::string, RaidItem> RaidMap;
            typedef std::map<std::string, LogicalVolumeItem> LogicalVolumeMap;
            typedef std::map<std::string, TargetItem> TargetMap;
            RaidMap raidMap_;
            LogicalVolumeMap logicalVolumeMap_;
            TargetMap targetMap_;
        private:
            const std::string makeLogicalVolumeKey(const std::string &logicalVolumeName,
                                                   const std::string &parentVolumeGroupName) const;

            bool isLunInTargetExists(const std::string &targetName, const unsigned int lunNumber);

            std::string getRaidSize(const std::string &raidPath);

            void recalculateUsePercentage(const std::string &volumeGroup);

        };
    }
}

