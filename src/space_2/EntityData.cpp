#include "EntityData.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_FLASHINGLIGHTS	"flashinglights"


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


//*************************************************************
// Methods
//*************************************************************
void EntityData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_FLASHINGLIGHTS))
		this->setFlashingLightJson(p_config->getString(CONFIG_FLASHINGLIGHTS));
}

void EntityData::loadFromEntityData( EntityData* p_data )
{
	this->setFlashingLightJson(p_data->getFlashingLightJson());
}

void EntityData::notifyFlashingLightJsonChanged()
{

}
