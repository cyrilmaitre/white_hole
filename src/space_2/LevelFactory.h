#pragma once
#include "LevelCharacter.h"
#include "LevelShip.h"
#include "Factory.h"

// Define 
#define CHARACTERLEVEL_CONFIG	"characterlevel"

class LevelFactory : public Factory<Level>
{
public:
	// Constructor - Destructor
	LevelFactory(void);
	~LevelFactory(void);

	// Methods
	LevelCharacter* getLevelCharacter();

	// Static 
	static LevelFactory* mInstance;
};

