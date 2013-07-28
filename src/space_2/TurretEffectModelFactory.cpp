#include "TurretEffectModelFactory.h"


//*************************************************************
// Init static
//*************************************************************
TurretEffectModelFactory * TurretEffectModelFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
TurretEffectModelFactory::TurretEffectModelFactory(void)
{
}

TurretEffectModelFactory::~TurretEffectModelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
TurretEffectModel * TurretEffectModelFactory::getTurretEffectModel( std::string p_configName, bool p_useLoaded /*= true*/ )
{
	TurretEffectModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new TurretEffectModel(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

TurretEffectModel * TurretEffectModelFactory::getTurretEffectModel( long p_id, bool p_useLoaded /*= true*/ )
{
	return TurretEffectModelFactory::getTurretEffectModel(TURRETEFFECTMODEL_CONFIG + Tools::buildStringWithLong(p_id), p_useLoaded);
}
