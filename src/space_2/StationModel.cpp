#include "StationModel.h"
#include "Tools.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationModel::StationModel(KeyValueFile* p_config)
{
	this->loadFromConfig(p_config);
}

StationModel::~StationModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long StationModel::getId()
{
	return this->mId;
}

void StationModel::setId( long p_id )
{
	this->mId = p_id;
}

std::string StationModel::getSprite()
{
	return this->mSprite;
}

void StationModel::setSprite( std::string p_sprite )
{
	this->mSprite  = p_sprite;
}


//*************************************************************
// Methods
//*************************************************************
void StationModel::loadFromConfig( KeyValueFile* p_config )
{
	DestructableData::loadFromConfig(p_config);
	MapObjectData::loadFromConfig(p_config);
	this->loadNpcDataFromConfig(p_config);

	this->setId(p_config->getLong(STATIONMODEL_CONFIG_ID));
	this->setSprite(p_config->getString(STATIONMODEL_CONFIG_SPRITE));
}
