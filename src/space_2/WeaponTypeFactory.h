#pragma once
#include "WeaponType.h"
#include "Factory.h"

class WeaponType;

// Define
#define WEAPONTYPE_CONFIG		"weapontype-"

class WeaponTypeFactory: public Factory<WeaponType>
{
public:
	// Constructor - Destructor
	WeaponTypeFactory(void);
	~WeaponTypeFactory(void);

	// Methods
	WeaponType* getWeaponType(std::string p_configName, bool p_useLoaded = true);
	WeaponType* getWeaponType(long p_id, bool p_useLoaded = true);

	// Static
	static WeaponTypeFactory *mInstance;
};

