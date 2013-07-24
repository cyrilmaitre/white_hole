#pragma once
#include "AmmoModel.h"
#include "Factory.h"

class AmmoModel;

// Define
#define AMMO_CONFIG		"ammomodel-"

class AmmoModelFactory: public Factory<AmmoModel>
{
public:
	// Constructor - Destructor
	AmmoModelFactory(void);
	~AmmoModelFactory(void);

	// Methods
	AmmoModel *getAmmo(std::string p_configName, bool p_useLoaded = true);
	AmmoModel *getAmmo(long p_id, bool p_useLoaded = true);

	// Static 
	static AmmoModelFactory *mInstance;

};

