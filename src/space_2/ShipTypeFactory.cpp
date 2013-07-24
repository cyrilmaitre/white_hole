#include "ShipTypeFactory.h"


//*************************************************************
// Init static
//*************************************************************
ShipTypeFactory* ShipTypeFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
ShipTypeFactory::ShipTypeFactory(void)
{
}

ShipTypeFactory::~ShipTypeFactory(void)
{
}


//*************************************************************
// Methode
//*************************************************************
ShipType* ShipTypeFactory::getShipType( std::string p_configShipType, bool p_useLoaded )
{
	ShipType* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configShipType);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new ShipType(Resource::resource->getConfig(p_configShipType));

		if(p_useLoaded)
			this->addObject(p_configShipType, returnValue);

		return returnValue;
	}
}

ShipType* ShipTypeFactory::getShipType( int p_id, bool p_useLoaded )
{
	return ShipTypeFactory::getShipType(SHIPTYPE_CONFIG+Tools::buildStringWithInt(p_id), p_useLoaded);
}