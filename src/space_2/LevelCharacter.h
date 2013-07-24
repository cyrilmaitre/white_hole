#pragma once
#include "Level.h"

// Define
#define LEVELCHARACTER_CONFIG_SKILLPOINTSONLEVELUP		"skillpoints_onlevelup"

class LevelCharacter : public Level
{
public:
	// Constructor - Destructor
	LevelCharacter(KeyValueFile* p_config);
	~LevelCharacter(void);

	// Getters - Setters
	int getSkillPointsOnLevelUp();
	void setSkillPointsOnLevelUp(int p_points);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	int mSkillPointsOnLevelup;
};

