#pragma once
#include "KeyValueFile.h"

// Define 
#define WEAPONABLEDATA_CONFIG_WEAPONSLOTMAX		"weapon_slot"

class WeaponableData
{
public:
	// Constructor - Destructor
	WeaponableData(void);
	~WeaponableData(void);

	// Getters - Setters
	virtual int getWeaponSlotMax();
	void setWeaponSlotMax(int p_slotMax);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromWeaponableData(WeaponableData* p_object);


protected:
	// Attributs
	int mWeaponSlotMax;
};

