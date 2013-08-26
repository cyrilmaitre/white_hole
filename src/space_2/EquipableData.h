#pragma once
#include "StuffableData.h"
#include "WeaponableData.h"
#include "UpgradableData.h"


class EquipableData : public UpgradableData, public StuffableData, public WeaponableData
{
public:
	// Constructor - Destructor
	EquipableData(void);
	~EquipableData(void);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromEquipableData(EquipableData* p_data);
};

