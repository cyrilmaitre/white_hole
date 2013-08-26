#include "EquipableData.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
EquipableData::EquipableData(void)
{
}

EquipableData::~EquipableData(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void EquipableData::loadFromConfig( KeyValueFile* p_config )
{
	UpgradableData::loadFromConfig(p_config);
	StuffableData::loadFromConfig(p_config);
	WeaponableData::loadFromConfig(p_config);
}

void EquipableData::loadFromEquipableData( EquipableData* p_data )
{
	UpgradableData::loadFromUpgradableData(p_data);
	StuffableData::loadFromStuffableData(p_data);
	WeaponableData::loadFromWeaponableData(p_data);
}
