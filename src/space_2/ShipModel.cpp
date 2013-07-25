#include "ShipModel.h"
#include "FactoryGet.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ShipModel::ShipModel( KeyValueFile* p_config ) : mShipType(NULL), MapObjectModel(p_config), Item(p_config->getInt("id"))
{
	this->loadFromConfig(p_config);
}

ShipModel::~ShipModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ShipType* ShipModel::getShipType()
{
	return this->mShipType;
}

void ShipModel::setShipType( ShipType *p_shipType )
{
	this->mShipType = p_shipType;
}


//*************************************************************
// Methode
//*************************************************************
void ShipModel::loadFromConfig( KeyValueFile* p_config )
{
	this->DestructableData::loadFromConfig(p_config);
	this->MovableData::loadFromConfig(p_config);
	this->ContainerableData::loadFromConfig(p_config);
	this->WeaponableData::loadFromConfig(p_config);
	this->UpgradableData::loadFromConfig(p_config);
	this->StuffableData::loadFromConfig(p_config);
	this->RotableData::loadFromConfig(p_config);
	this->EntityMovableData::loadFromConfig(p_config);
	this->EntityData::loadFromConfig(p_config);

	this->setShipType(FactoryGet::getShipTypeFactory()->getShipType(p_config->getLong("ship_type")));
}


