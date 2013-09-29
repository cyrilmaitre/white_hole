#pragma once
#include "Resource.h"
#include "KeyValueFile.h"


class Level
{
public:
	// Constructor - Destructor
	Level(KeyValueFile* p_config);
	~Level(void);

	// Getters - Setters
	long getLevelCoeff();
	void setLevelCoeff(long p_coeff);
	
	int getLevelMax();
	void setLevelMax(int p_max);

	int getSkillPointsOnLevelUp();
	void setSkillPointsOnLevelUp(int p_points);

	long getExperience(int p_level);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	long mLevelCoeff;
	int mLevelMax;
	int mSkillPointsOnLevelup;
};

