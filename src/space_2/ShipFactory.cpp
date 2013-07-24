#include "ShipFactory.h"
#include "ShipModelFactory.h"
#include "LevelManager.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ShipFactory::ShipFactory(void)
{
}

ShipFactory::~ShipFactory(void)
{
}


//*************************************************************
// Methode
//*************************************************************
Ship* ShipFactory::getShip( ShipModel* p_shipModel )
{
	Ship* tmpShip = new Ship();
	tmpShip->setShipModel(p_shipModel);

	return tmpShip;
}