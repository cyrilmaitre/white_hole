#include "LevelShip.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
LevelShip::LevelShip( KeyValueFile* p_config ) : Level(p_config)
{
	this->loadFromConfig(p_config);
}

LevelShip::~LevelShip(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************


//*************************************************************
// Methods
//*************************************************************
void LevelShip::loadFromConfig( KeyValueFile* p_config )
{

}

