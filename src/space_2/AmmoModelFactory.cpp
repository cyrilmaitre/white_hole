#include "AmmoModelFactory.h"


//*************************************************************
// Init static
//*************************************************************
AmmoModelFactory * AmmoModelFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
AmmoModelFactory::AmmoModelFactory(void)
{
}

AmmoModelFactory::~AmmoModelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
AmmoModel * AmmoModelFactory::getAmmo( std::string p_configName, bool p_useLoaded )
{
	AmmoModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new AmmoModel(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

AmmoModel * AmmoModelFactory::getAmmo( long p_id, bool p_useLoaded )
{
	return AmmoModelFactory::getAmmo(AMMO_CONFIG+Tools::buildStringWithLong(p_id), p_useLoaded);
}
