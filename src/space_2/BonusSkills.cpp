#include "BonusSkills.h"
#include "SplitString.h"
#include "IdValueInt.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
BonusSkills::BonusSkills(void)
{
}

BonusSkills::~BonusSkills(void)
{
}


//*************************************************************
// Getters - Setter
//*************************************************************
int BonusSkills::getBonusSkill( long p_skillId )
{
	std::map<long, int>::iterator it;
	it = this->mBonusSkill.find(p_skillId);

	if(it != this->mBonusSkill.end())
		return it->second;
	else
		return 0;
}

void BonusSkills::setBonusSkill( std::string p_bonus )
{
	if(p_bonus != "NULL")
	{
		SplitString splitBonus(p_bonus, ";");
		for(int i = 0; i < splitBonus.getSplitCount(); i++)
		{
			IdValueInt currentBonus(splitBonus.getSplitString(i));
			this->mBonusSkill.insert(std::pair<long, int>(currentBonus.getId(), currentBonus.getValue()));
		}
	}
}
