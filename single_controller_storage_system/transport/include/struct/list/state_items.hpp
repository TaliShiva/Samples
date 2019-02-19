#pragma once

#include <string>
#include <vector>
typedef std::vector<std::string> StringVector;
/**
 * @struct  - структара описания RAID и подключенной к нему LVM volume group
 */
typedef struct {
    std::string raidPath;
    std::string raidLevel;
    std::string raidSize;
    std::string volumeGroupName = "";
    std::string volumeGroupUsedPercentile = "";
    StringVector raidDevices;
} RaidItem;

typedef std::vector<RaidItem> RaidItemList;
/**
 * @struct - структура описания LVM logic volume,
 * его имени при подключении к SCST и подключенного к нему кэша
 */
typedef struct {
    std::string logicalVolumeName;
    std::string logicalVolumeSize;
    std::string volumeGroupName;
    /**
     * @brief vDiskName - имя диска внутри SCST
     */
    std::string vDiskName = "";
    bool cached = false;
    std::string cachedDeviceName = "";
} LogicalVolumeItem;

typedef std::vector<LogicalVolumeItem> LogicalVolumeItemList;
/**
 * @struct стуктура описания LUN в SCST
 */
typedef struct {
    unsigned int lunNumber;
    /**
     * @brief vDiskName - имя подключенного к SCST диска
     */
    std::string vDiskName;
} LunItem;
/**
 * @brief LunItemVector - вектор лунов
 */
typedef std::vector<LunItem> LunItemList;

/**
 * @struct - структура описания таргета в SCST
 */
typedef struct {
    std::string targetName;
    bool enabled;
    /**
     * @brief lunItems - список лунов, принадлежащих данному таргету
     */
    LunItemList lunItems;
} TargetItem;

typedef std::vector<TargetItem> TargetItemList;