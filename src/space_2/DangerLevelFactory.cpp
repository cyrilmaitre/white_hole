#include "DangerLevelFactory.h"


//*************************************************************
// Init static 
//*************************************************************
DangerLevelFactory* DangerLevelFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
DangerLevelFactory::DangerLevelFactory(void)
{
}


DangerLevelFactory::~DangerLevelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
DangerLevel * DangerLevelFactory::getDangerLevel( std::string p_configName, bool p_useLoaded )
{
	DangerLevel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new DangerLevel(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

DangerLevel * DangerLevelFactory::getDangerLevel( long p_jobId, bool p_useLoaded )
{
	return this->getDangerLevel(DANGERLEVEL_CONFIG + Tools::buildStringWithLong(p_jobId), p_useLoaded);
}
