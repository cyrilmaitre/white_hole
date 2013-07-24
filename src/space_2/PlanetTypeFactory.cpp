#include "PlanetTypeFactory.h"


//*************************************************************
// Init static
//*************************************************************
PlanetTypeFactory * PlanetTypeFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
PlanetTypeFactory::PlanetTypeFactory(void)
{
}

PlanetTypeFactory::~PlanetTypeFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
PlanetType * PlanetTypeFactory::getPlanetType( std::string p_configName, bool p_useLoaded )
{
	PlanetType* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new PlanetType(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

PlanetType * PlanetTypeFactory::getPlanetType( long p_id, bool p_useLoaded )
{
	return this->getPlanetType(PLANETTYPE_CONFIG + Tools::buildStringWithLong(p_id), p_useLoaded);
}
