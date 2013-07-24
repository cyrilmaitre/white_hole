#include "Level.h"
#include "SplitString.h"


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
int Level::getLevelMin()
{
	int levelMin = 0;
	for( std::map<int, long>::iterator it = this->mLevels.begin() ; it != this->mLevels.end(); it++ )
	{
		if((*it).first < levelMin)
			levelMin = (*it).first;
	}
	return levelMin;
}

int Level::getLevelMax()
{
	int levelMax = 0;
	for( std::map<int, long>::iterator it = this->mLevels.begin() ; it != this->mLevels.end(); it++ )
	{
		if((*it).first > levelMax)
			levelMax = (*it).first + 1;
	}
	return levelMax;
}

long Level::getExperience( int p_level )
{
	for( std::map<int, long>::iterator it = this->mLevels.begin() ; it != this->mLevels.end(); it++ )
	{
		if((*it).first == p_level)
			return (*it).second;
	}
	return -1;
}


//*************************************************************
// Methods
//*************************************************************
void Level::loadFromConfig( KeyValueFile* p_config )
{
	std::string levels = p_config->getString(LEVEL_CONFIG_LEVELS);
	SplitString levelsExploded(levels, ";");
	for(int i = 0; i < levelsExploded.getSplitCount(); i++)
	{
		std::string levelString = levelsExploded.getSplitString(i);
		int startDelimeter = levelString.find("(");
		int endDemimeter = levelString.find(")");
		this->mLevels.insert(std::pair<int, long>(Tools::getIntFromString(levelString.substr(0, startDelimeter)), Tools::getLongFromString(levelString.substr(startDelimeter+1, endDemimeter-startDelimeter-1))));
	}
}
