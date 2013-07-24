#pragma once
#include "PlanetType.h"
#include "Factory.h"

// Define
#define PLANETTYPE_CONFIG	"planettype-"

class PlanetTypeFactory : public Factory<PlanetType>
{
public:
	// Constructor - Destructor
	PlanetTypeFactory(void);
	~PlanetTypeFactory(void);

	// Methods
	PlanetType *getPlanetType(std::string p_configName, bool p_useLoaded = true);
	PlanetType *getPlanetType(long p_id, bool p_useLoaded = true);

	// Static
	static PlanetTypeFactory *mInstance;
};

