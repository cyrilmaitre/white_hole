#include "Race.h"
#include "SpriteParameterFactory.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Race::Race( KeyValueFile *p_config )
{
	this->mAvatarIndex = NULL;
	this->loadFromConfig(p_config);
}

Race::~Race(void)
{
	this->deleteAvatarIndex();	
}

void Race::deleteAvatarIndex()
{
	if(this->mAvatarIndex != NULL)
		delete this->mAvatarIndex;
}


//*************************************************************
// Getters - Setters
//*************************************************************
long Race::getId()
{
	return this->mId;
}

void Race::setId( long p_id )
{
	this->mId = p_id;
}

std::string Race::getName()
{
	return this->mName;
}

void Race::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string Race::getDescription()
{
	return this->mDescription;
}

void Race::setDescription( std::string p_description )
{
	this->mDescription = p_description;
}

std::string Race::getSpriteId()
{
	return this->mSpriteId;
}

void Race::setSpriteId( std::string p_id )
{
	this->mSpriteId = p_id;
}

int Race::getAvatarCount()
{
	return this->mAvatarIndex->getSplitCount();
}

std::string Race::getAvatarIndex( int p_index )
{
	return this->mAvatarIndex->getSplitString(p_index);
}

void Race::setAvatarIndex( std::string p_indexes )
{
	this->deleteAvatarIndex();
	this->mAvatarIndex = new SplitString(p_indexes, ";");
}


//*************************************************************
// Methods
//*************************************************************
void Race::loadFromConfig( KeyValueFile *p_config )
{
	this->setId(p_config->getLong(RACE_CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(RACE_CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(RACE_CONFIG_DESCRIPTION)));
	this->setSpriteId(p_config->getString(RACE_CONFIG_SPRITEID));
	this->setAvatarIndex(p_config->getString(RACE_CONFIG_AVATARINDEX));
	this->setBonusSkill(p_config->getString(RACE_CONFIG_BONUS));
}



