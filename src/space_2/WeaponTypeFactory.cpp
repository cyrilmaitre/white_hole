#include "WeaponTypeFactory.h"


//*************************************************************
// Init static
//*************************************************************
WeaponTypeFactory * WeaponTypeFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
WeaponTypeFactory::WeaponTypeFactory(void)
{
}

WeaponTypeFactory::~WeaponTypeFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
WeaponType* WeaponTypeFactory::getWeaponType( std::string p_configName, bool p_useLoaded )
{
	WeaponType* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new WeaponType(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

WeaponType* WeaponTypeFactory::getWeaponType( long p_id, bool p_useLoaded )
{
	return WeaponTypeFactory::getWeaponType(WEAPONTYPE_CONFIG+Tools::buildStringWithLong(p_id), p_useLoaded);
}
