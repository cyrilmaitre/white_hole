#include "NpcShipModelFactory.h"



//*************************************************************
// Init static
//*************************************************************
NpcShipModelFactory * NpcShipModelFactory::mInstance;



//*************************************************************
// Constructor - Destructor
//*************************************************************
NpcShipModelFactory::NpcShipModelFactory(void)
{
}

NpcShipModelFactory::~NpcShipModelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
NpcShipModel * NpcShipModelFactory::getNpcShipModel( std::string p_configName, bool p_useLoaded )
{
	NpcShipModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new NpcShipModel(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

NpcShipModel * NpcShipModelFactory::getNpcShipModel( long p_id, bool p_useLoaded )
{
	return NpcShipModelFactory::getNpcShipModel(NPCSHIPMODEL_CONFIG+Tools::buildStringWithInt(p_id), p_useLoaded);
}
