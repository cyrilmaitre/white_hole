#include "NpcShipModel.h"
#include "FactoryGet.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
NpcShipModel::NpcShipModel( KeyValueFile *p_config )
{
	this->loadFromConfig(p_config);
}

NpcShipModel::~NpcShipModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long NpcShipModel::getIdNpcShipModel()
{
	return this->mIdNpcShipModel;
}

void NpcShipModel::setIdNpcShipModel( long p_id )
{
	this->mIdNpcShipModel = p_id;
}

std::string NpcShipModel::getName()
{
	return this->mName;
}

void NpcShipModel::setName( std::string p_name )
{
	this->mName = p_name;
}

ShipModel * NpcShipModel::getShipModel()
{
	return this->mShipModel;
}

void NpcShipModel::setShipModel( ShipModel *p_model )
{
	this->mShipModel = p_model;
}


//*************************************************************
// Methods
//*************************************************************
void NpcShipModel::loadFromConfig( KeyValueFile *p_config )
{
	NpcData::loadNpcDataFromConfig(p_config);

	if(p_config->has(NPCSHIPMODEL_CONFIG_ID))
		this->setIdNpcShipModel(p_config->getLong(NPCSHIPMODEL_CONFIG_ID));

	if(p_config->has(NPCSHIPMODEL_CONFIG_NAME))
		this->setName(p_config->getString(NPCSHIPMODEL_CONFIG_NAME));

	if(p_config->has(NPCSHIPMODEL_CONFIG_SHIPMODEL))
		this->setShipModel(FactoryGet::getShipModelFactory()->getShipModel(p_config->getLong(NPCSHIPMODEL_CONFIG_SHIPMODEL)));
}


