#include "AmmoTypeFactory.h"


//*************************************************************
// Init static
//*************************************************************
AmmoTypeFactory * AmmoTypeFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
AmmoTypeFactory::AmmoTypeFactory(void)
{
}

AmmoTypeFactory::~AmmoTypeFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
AmmoType * AmmoTypeFactory::getAmmoType( long p_id, bool p_useLoaded )
{
	return AmmoTypeFactory::getAmmoType(AMMOTYPE_CONFIG+Tools::buildStringWithLong(p_id), p_useLoaded);
}

AmmoType * AmmoTypeFactory::getAmmoType( std::string p_configName, bool p_useLoaded )
{
	AmmoType* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new AmmoType(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}
