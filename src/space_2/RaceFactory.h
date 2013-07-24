#pragma once
#include "Race.h"
#include "Factory.h"

class Race;

// Define
#define RACE_CONFIG				"race-"
#define RACE_CONFIG_HUMAN		RACE_CONFIG"1"
#define RACE_CONFIG_ANDROID		RACE_CONFIG"2"

class RaceFactory: public Factory<Race>
{
public:
	// Constructor - Destructor
	RaceFactory(void);
	~RaceFactory(void);

	// Methods
	Race* getRaceHuman();
	Race* getRaceAndroid();
	Race* getRace(std::string p_configName, bool p_useLoaded = true);
	Race* getRace(long p_raceId, bool p_useLoaded = true);

	// Static
	static RaceFactory *mInstance;
};

