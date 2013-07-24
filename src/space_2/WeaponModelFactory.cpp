#include "WeaponModelFactory.h"


//*************************************************************
// Init static
//*************************************************************
WeaponModelFactory * WeaponModelFactory::mInstance;



//*************************************************************
// Constructor - Destructor
//*************************************************************
WeaponModelFactory::WeaponModelFactory(void)
{
}

WeaponModelFactory::~WeaponModelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
WeaponModel * WeaponModelFactory::getWeaponModel( std::string p_configName, bool p_useLoaded )
{
	WeaponModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new WeaponModel(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

WeaponModel * WeaponModelFactory::getWeaponModel( long p_id, bool p_useLoaded )
{
	return WeaponModelFactory::getWeaponModel(WEAPONMODEL_CONFIG+Tools::buildStringWithLong(p_id), p_useLoaded);
}
