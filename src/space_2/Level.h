#pragma once
#include "Resource.h"
#include "KeyValueFile.h"

// Define
#define LEVEL_CONFIG_LEVELS		"levels"

class Level
{
public:
	// Constructor - Destructor
	Level(KeyValueFile* p_config);
	~Level(void);

	// Getters - Setters
	int getLevelMin();
	int getLevelMax();

	long getExperience(int p_level);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	std::map<int, long> mLevels;
};

