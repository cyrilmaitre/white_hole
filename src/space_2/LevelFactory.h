#pragma once
#include "LevelCharacter.h"
#include "LevelShip.h"
#include "Factory.h"

// Define 
#define CHARACTERLEVEL_CONFIG	"characterlevel"
#define SHIPLEVEL_CONFIG		"shiplevel-"

class LevelFactory : public Factory<Level>
{
public:
	// Constructor - Destructor
	LevelFactory(void);
	~LevelFactory(void);

	// Methods
	LevelCharacter* getLevelCharacter();
	LevelShip* getLevelShip(std::string p_configName, bool p_useLoaded = true);
	LevelShip* getLevelShip(long p_id, bool p_useLoaded = true);

	// Static 
	static LevelFactory* mInstance;
};

