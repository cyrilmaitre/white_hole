#include "PlanetModelFactory.h"


//*************************************************************
// Init static
//*************************************************************
PlanetModelFactory * PlanetModelFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
PlanetModelFactory::PlanetModelFactory(void)
{
}

PlanetModelFactory::~PlanetModelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
PlanetModel * PlanetModelFactory::getPlanetModel( std::string p_configName, bool p_useLoaded )
{
	PlanetModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new PlanetModel(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}	
}

PlanetModel * PlanetModelFactory::getPlanetModel( long p_id, bool p_useLoaded )
{
	return this->getPlanetModel(PLANETMODEL_CONFIG + Tools::buildStringWithLong(p_id), p_useLoaded);
}
