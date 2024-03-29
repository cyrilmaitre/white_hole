#include "ShipModel.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_ID				"id"	
#define CONFIG_LEVELCONFIG		"levelconf"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ShipModel::ShipModel( KeyValueFile* p_config ) : MapObjectModel(p_config), Item(p_config->getInt(CONFIG_ID))
{
	this->loadFromConfig(p_config);
}

ShipModel::~ShipModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
LevelShip* ShipModel::getLevelShipConfig()
{
	return this->mLevelShipConfig;
}

void ShipModel::setLevelShipConfig( LevelShip* p_level )
{
	this->mLevelShipConfig = p_level;
}


//*************************************************************
// Methode
//*************************************************************
void ShipModel::loadFromConfig( KeyValueFile* p_config )
{
	this->DestructableData::loadFromConfig(p_config);
	this->MovableData::loadFromConfig(p_config);
	this->ContainerableData::loadFromConfig(p_config);
	this->EquipableData::loadFromConfig(p_config);
	this->RotableData::loadFromConfig(p_config);
	this->EntityMovableData::loadFromConfig(p_config);
	this->EntityData::loadFromConfig(p_config);

	if(p_config->has(CONFIG_LEVELCONFIG))
		this->setLevelShipConfig(FactoryGet::getLevelFactory()->getLevelShip(p_config->getString(CONFIG_LEVELCONFIG)));
}




