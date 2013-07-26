#include "EntityData.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_FLASHINGLIGHTS	"flashinglights"
#define CONFIG_RADARS			"radars"
#define CONFIG_TURRETS			"turrets"


//*************************************************************
// Constructor - Destructor
//*************************************************************
EntityData::EntityData(void)
{
}

EntityData::~EntityData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string EntityData::getFlashingLightJson()
{
	return this->mFlashingLightJson;
}

void EntityData::setFlashingLightJson( std::string p_json )
{
	if(this->mFlashingLightJson != p_json)
	{
		this->mFlashingLightJson = p_json;
		this->notifyFlashingLightJsonChanged();
	}
}

std::string EntityData::getRadarJson()
{
	return this->mRadarJson;
}

void EntityData::setRadarJson( std::string p_json )
{
	if(this->mRadarJson != p_json)
	{
		this->mRadarJson = p_json;
		this->notifyRadarJsonChanged();
	}
}

std::string EntityData::getTurretJson()
{
	return this->mTurretJson;
}

void EntityData::setTurretJson( std::string p_json )
{
	if(this->mTurretJson != p_json)
	{
		this->mTurretJson = p_json;
		this->notifyTurretJsonChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void EntityData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_FLASHINGLIGHTS))
		this->setFlashingLightJson(p_config->getString(CONFIG_FLASHINGLIGHTS));

	if(p_config->has(CONFIG_RADARS))
		this->setRadarJson(p_config->getString(CONFIG_RADARS));

	if(p_config->has(CONFIG_TURRETS))
		this->setTurretJson(p_config->getString(CONFIG_TURRETS));
}

void EntityData::loadFromEntityData( EntityData* p_data )
{
	this->setFlashingLightJson(p_data->getFlashingLightJson());
	this->setRadarJson(p_data->getRadarJson());
	this->setTurretJson(p_data->getTurretJson());
}

void EntityData::notifyFlashingLightJsonChanged()
{

}

void EntityData::notifyRadarJsonChanged()
{

}

void EntityData::notifyTurretJsonChanged()
{

}
