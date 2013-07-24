#pragma once
#include "Resource.h"
#include "KeyValueFile.h"

// Define
#define LEVELMANAGER_CONFIG_NAME	"characterlevel"

// TODO: TO REFRACTOR TO DO SAME AS DANGERLEVELMANAGER
class LevelManager
{
public:
	// Methods
	static void init();
	static int getLevelMinimum();
	static int getLevelMaximum();
	static long getExperienceLevelUp(int p_level);


private:
	// Attributs
	static KeyValueFile* levelConfig;

	// Constructor - Destructor
	LevelManager(void);
	~LevelManager(void);
};

