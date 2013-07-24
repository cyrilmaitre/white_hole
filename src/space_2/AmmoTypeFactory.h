#pragma once
#include "AmmoType.h"
#include "KeyValueFile.h"
#include "Factory.h"

class AmmoType;

// Define
#define AMMOTYPE_CONFIG		"ammotype-"

class AmmoTypeFactory: public Factory<AmmoType>
{
public:
	// Constructor - Destructor
	AmmoTypeFactory(void);
	~AmmoTypeFactory(void);

	// Methods
	AmmoType *getAmmoType(std::string p_configName, bool p_useLoaded = true);
	AmmoType *getAmmoType(long p_id, bool p_useLoaded = true);

	// Static 
	static AmmoTypeFactory *mInstance;
};

