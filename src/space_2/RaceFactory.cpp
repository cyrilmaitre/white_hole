#include "RaceFactory.h"


//*************************************************************
// Init static
//*************************************************************
RaceFactory * RaceFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
RaceFactory::RaceFactory(void)
{
}

RaceFactory::~RaceFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
Race* RaceFactory::getRace( std::string p_configName, bool p_useLoaded )
{
	Race* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new Race(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

Race* RaceFactory::getRace( long p_raceId, bool p_useLoaded )
{
	return this->getRace(RACE_CONFIG+Tools::buildStringWithLong(p_raceId), p_useLoaded);
}

Race* RaceFactory::getRaceHuman()
{
	return this->getRace(RACE_CONFIG_HUMAN);
}

Race* RaceFactory::getRaceAndroid()
{
	return this->getRace(RACE_CONFIG_ANDROID);
}
