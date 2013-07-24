#include "ShipModelFactory.h"


//*************************************************************
// Static init
//*************************************************************
ShipModelFactory * ShipModelFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
ShipModelFactory::ShipModelFactory(void)
{
}

ShipModelFactory::~ShipModelFactory(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ShipModel* ShipModelFactory::getShipModel( std::string p_configShipModel, bool p_useLoaded )
{
	ShipModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configShipModel);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new ShipModel(Resource::resource->getConfig(p_configShipModel));

		if(p_useLoaded)
			this->addObject(p_configShipModel, returnValue);

		return returnValue;
	}
}

ShipModel* ShipModelFactory::getShipModel( long p_id, bool p_useLoaded )
{
	return ShipModelFactory::getShipModel(SHIPMODEL_CONFIG+Tools::buildStringWithLong(p_id), p_useLoaded);
}
