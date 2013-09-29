#include "LevelFactory.h"


//*************************************************************
// Init static
//*************************************************************
LevelFactory* LevelFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
LevelFactory::LevelFactory(void)
{
}

LevelFactory::~LevelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
LevelCharacter* LevelFactory::getLevelCharacter()
{
	LevelCharacter* returnValue = NULL;
	returnValue = (LevelCharacter*)this->getObject(CHARACTERLEVEL_CONFIG);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new LevelCharacter(Resource::resource->getConfig(CHARACTERLEVEL_CONFIG));
		this->addObject(CHARACTERLEVEL_CONFIG, returnValue);
		return returnValue;
	}
}

LevelShip* LevelFactory::getLevelShip( std::string p_configName, bool p_useLoaded )
{
	LevelShip* returnValue = NULL;

	if(p_useLoaded)
		returnValue = (LevelShip*)this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new LevelShip(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

LevelShip* LevelFactory::getLevelShip( long p_id, bool p_useLoaded )
{
	return this->getLevelShip(SHIPLEVEL_CONFIG + Tools::buildStringWithInt(p_id), p_useLoaded);
}
