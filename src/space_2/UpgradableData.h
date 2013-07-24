#pragma once
#include "KeyValueFile.h"

// Define
#define UPGRADBLEDATA_CONFIG_UPGRADESLOTMAX		"upgrade_slot"

class UpgradableData
{
public:
	// Constructor - Destructor
	UpgradableData(void);
	~UpgradableData(void);

	// Getters - Setters
	virtual int getUpgradeSlotMax();
	void setUpgradeSlotMax(int p_slotMax);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromUpgradableData(UpgradableData* p_object);


protected:
	// Atrributs
	int mUpgradeSlotMax;
};

