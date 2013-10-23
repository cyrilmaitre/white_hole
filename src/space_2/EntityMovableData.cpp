#include "EntityMovableData.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_REACTORS			"reactors"
#define CONFIG_REACTORSOUND		"reactor_sound"


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

std::string EntityMovableData::getReactorSound()
{
	return this->mReactorSound;
}

void EntityMovableData::setReactorSound( std::string p_sound )
{
	if(this->mReactorSound != p_sound)
	{
		this->mReactorSound = p_sound;
		this->notifyReactorSoundChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void EntityMovableData::loadFromConfig(KeyValueFile* p_config)
{
	if(p_config->has(CONFIG_REACTORS))
		this->setReactorJson(p_config->getString(CONFIG_REACTORS));

	if(p_config->has(CONFIG_REACTORSOUND))
		this->setReactorSound(p_config->getString(CONFIG_REACTORSOUND));
}

void EntityMovableData::loadFromEntityMovableData(EntityMovableData* p_data)
{
	this->setReactorJson(p_data->getReactorJson());
	this->setReactorSound(p_data->getReactorSound());
}

void EntityMovableData::notifyReactorJsonChanged()
{

}

void EntityMovableData::notifyReactorSoundChanged()
{

}

