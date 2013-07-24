#pragma once
#include "KeyValueFile.h"
#include "Level.h"


class Levelable
{
public:
	// Constructor - Destructor
	Levelable(void);
	~Levelable(void);

	// Getters - Setters
	int getLevel();
	void setLevel(int p_level);
	bool isLevelChanged();
	bool isLevelMax();

	long getExperience();
	long getExperienceCurrentLevel();
	long getExperienceBeforeLevel();
	void setExperience(long p_experience);
	bool isExperienceChanged();

	bool hasLevelConfig();
	Level* getLevelConfig();
	void setLevelConfig(Level *p_level);

	// Methods
	virtual void incLevel();
	virtual void incExperience(long p_inc);
	virtual void notifyExperienceChanged();
	virtual void notifyLevelChanged();


private:
	// Attributs
	int mLevel;
	bool mLevelChanged;
	long mExperience;
	bool mExperienceChanged;
	Level *mLevelConfig;
};

