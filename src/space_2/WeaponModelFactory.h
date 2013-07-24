#pragma once
#include "WeaponModel.h"
#include "Factory.h"

class WeaponModel;

// Define
#define WEAPONMODEL_CONFIG		"weaponmodel-"

class WeaponModelFactory: public Factory<WeaponModel>
{
public:
	// Constructor - Destructor 
	WeaponModelFactory(void);
	~WeaponModelFactory(void);

	// Method
	WeaponModel *getWeaponModel(std::string p_configName, bool p_useLoaded = true);
	WeaponModel *getWeaponModel(long p_id, bool p_useLoaded = true);


	// Static
	static WeaponModelFactory *mInstance;
};

