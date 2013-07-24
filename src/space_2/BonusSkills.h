#pragma once
#include "Resource.h"


class BonusSkills
{
public:
	// Getters - Setters
	int getBonusSkill(long p_skillId);


protected:
	// Constructor - Destructor
	BonusSkills(void);
	~BonusSkills(void);

	// Attributs
	std::map<long, int> mBonusSkill;

	// Getters - Setter
	void setBonusSkill(std::string p_bonus);
};

