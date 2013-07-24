#pragma once
#include "Level.h"


class LevelShip : public Level
{
public:
	// Constructor - Destructor
	LevelShip(KeyValueFile* p_config);
	~LevelShip(void);

	// Getters - Setters

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
};

