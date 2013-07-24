#pragma once
#include "DangerLevel.h"
#include "Factory.h"

// Define
#define DANGERLEVEL_CONFIG	"dangerlevel-"

class DangerLevelFactory: public Factory<DangerLevel>
{
public:
	// Constructor - Destructor
	DangerLevelFactory(void);
	~DangerLevelFactory(void);

	// Methods
	DangerLevel *getDangerLevel(std::string p_configName, bool p_useLoaded = true);
	DangerLevel *getDangerLevel(long p_jobId, bool p_useLoaded = true);

	// Static 
	static DangerLevelFactory* mInstance;
};

