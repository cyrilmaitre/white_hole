#include "StarModelFactory.h"

//*************************************************************
// Define
//*************************************************************
#define CONFIG_NAME		"starmodel-"


//*************************************************************
// Init static
//*************************************************************
StarModelFactory * StarModelFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
StarModelFactory::StarModelFactory(void)
{
}

StarModelFactory::~StarModelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
StarModel * StarModelFactory::getStarModel( std::string p_configName, bool p_useLoaded )
{
	StarModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new StarModel(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}	
}

StarModel * StarModelFactory::getStarModel( long p_id, bool p_useLoaded )
{
	return this->getStarModel(CONFIG_NAME + Tools::buildStringWithLong(p_id), p_useLoaded);
}
