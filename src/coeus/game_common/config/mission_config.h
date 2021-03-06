#ifndef __MISSION_CONFIG_H__
#define __MISSION_CONFIG_H__

#include "configuration.h"
#include "game_common/mission.h"

class MissionConfig
    : public Configuration, public Venus::Singleton<MissionConfig>
{
public:
    MissionConfig();
    virtual ~MissionConfig();

public:
    bool parse();
    const MissionData* getMissionDataById(uint32 missionId) const;

public:
    adap_map<uint32, MissionData> _missions;
};

#endif // !__MISSION_CONFIG_H__
