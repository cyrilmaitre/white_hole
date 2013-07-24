#pragma once
#include "Factory.h"
#include "PlanetModel.h"

// Define
#define PLANETMODEL_CONFIG		"planetmodel-"

class PlanetModelFactory : public Factory<PlanetModel>
{
public:
	// Constructor - Destructor
	PlanetModelFactory(void);
	~PlanetModelFactory(void);

	// Methods
	PlanetModel *getPlanetModel(std::string p_configName, bool p_useLoaded = true);
	PlanetModel *getPlanetModel(long p_id, bool p_useLoaded = true);

	// Static
	static PlanetModelFactory *mInstance;
};

