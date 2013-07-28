#pragma once
#include "Factory.h"
#include "TurretEffectModel.h"

// Define
#define TURRETEFFECTMODEL_CONFIG		"turreteffectmodel-"

class TurretEffectModelFactory : public Factory<TurretEffectModel>
{
public:
	// Constructor - Destructor
	TurretEffectModelFactory(void);
	~TurretEffectModelFactory(void);

	// Methods
	TurretEffectModel *getTurretEffectModel(std::string p_configName, bool p_useLoaded = true);
	TurretEffectModel *getTurretEffectModel(long p_id, bool p_useLoaded = true);

	// Static 
	static TurretEffectModelFactory *mInstance;
};

