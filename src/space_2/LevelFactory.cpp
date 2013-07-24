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
