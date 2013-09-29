#include "Level.h"
#include "SplitString.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_LEVELCOEFF				"level_coeff"
#define CONFIG_LEVELMAX					"level_max"
#define CONFIG_SPONLU					"skillpoints_onlevelup"
#define EXPERIENCE_EQUATION_CONST		50


//*************************************************************
// Constructor - Destructor
//*************************************************************
Level::Level(KeyValueFile* p_config)
{
	this->loadFromConfig(p_config);
}

Level::~Level(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int Level::getLevelMax()
{
	return this->mLevelMax;
}

void Level::setLevelMax( int p_max )
{
	this->mLevelMax = p_max;
}

long Level::getLevelCoeff()
{
	return this->mLevelCoeff;
}

void Level::setLevelCoeff( long p_coeff )
{
	this->mLevelCoeff = p_coeff;
}

int Level::getSkillPointsOnLevelUp()
{
	return this->mSkillPointsOnLevelup;
}

void Level::setSkillPointsOnLevelUp( int p_points )
{
	this->mSkillPointsOnLevelup = p_points;
}

long Level::getExperience( int p_level )
{
	int nextLevel = p_level + 1;
	return (this->mLevelCoeff * nextLevel) / (nextLevel + EXPERIENCE_EQUATION_CONST);
}


//*************************************************************
// Methods
//*************************************************************
void Level::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_LEVELCOEFF))
		this->setLevelCoeff(p_config->getLong(CONFIG_LEVELCOEFF));

	if(p_config->has(CONFIG_LEVELMAX))
		this->setLevelMax(p_config->getInt(CONFIG_LEVELMAX));

	if(p_config->has(CONFIG_SPONLU))
		this->setSkillPointsOnLevelUp(p_config->getInt(CONFIG_SPONLU));
}
