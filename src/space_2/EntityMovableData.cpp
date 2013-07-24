#include "EntityMovableData.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_REACTORS			"reactors"


//*************************************************************
// Constructor - Destructor
//*************************************************************
EntityMovableData::EntityMovableData(void)
{
}

EntityMovableData::~EntityMovableData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string EntityMovableData::getReactorJson()
{
	return this->mReactorJson;
}

void EntityMovableData::setReactorJson( std::string p_json )
{
	if(this->mReactorJson != p_json)
	{
		this->mReactorJson = p_json;
		this->notifyReactorJsonChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void EntityMovableData::loadFromConfig(KeyValueFile* p_config)
{
	if(p_config->has(CONFIG_REACTORS))
		this->setReactorJson(p_config->getString(CONFIG_REACTORS));
}

void EntityMovableData::loadFromEntityMovableData(EntityMovableData* p_data)
{
	this->setReactorJson(p_data->getReactorJson());
}

void EntityMovableData::notifyReactorJsonChanged()
{

}
