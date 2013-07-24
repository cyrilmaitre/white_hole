#include "LevelManager.h"
#include "Tools.h"


//*************************************************************
// Static init
//*************************************************************
KeyValueFile* LevelManager::levelConfig;


//*************************************************************
// Constructor - Destructor
//*************************************************************
LevelManager::LevelManager(void)
{
}

LevelManager::~LevelManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
void LevelManager::init()
{
	LevelManager::levelConfig = Resource::resource->getConfig(LEVELMANAGER_CONFIG_NAME);
}

int LevelManager::getLevelMinimum()
{
	return LevelManager::levelConfig->getInt("level_min");
}

int LevelManager::getLevelMaximum()
{
	return LevelManager::levelConfig->getInt("level_max");
}

long LevelManager::getExperienceLevelUp( int p_level )
{
	if(p_level < LevelManager::getLevelMinimum() || p_level > LevelManager::getLevelMaximum())
		return -1;
	
	return LevelManager::levelConfig->getLong(Tools::formatInt(p_level));	
}