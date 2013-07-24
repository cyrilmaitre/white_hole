#include "LevelCharacter.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
LevelCharacter::LevelCharacter(KeyValueFile* p_config) : Level(p_config)
{
	this->loadFromConfig(p_config);
}

LevelCharacter::~LevelCharacter(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int LevelCharacter::getSkillPointsOnLevelUp()
{
	return this->mSkillPointsOnLevelup;
}

void LevelCharacter::setSkillPointsOnLevelUp( int p_points )
{
	this->mSkillPointsOnLevelup = p_points;
}


//*************************************************************
// Methods
//*************************************************************
void LevelCharacter::loadFromConfig( KeyValueFile* p_config )
{
	this->setSkillPointsOnLevelUp(p_config->getInt(LEVELCHARACTER_CONFIG_SKILLPOINTSONLEVELUP));
}

