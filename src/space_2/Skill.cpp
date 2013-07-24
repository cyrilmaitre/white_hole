#include "Skill.h"
#include "SkillFactory.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Skill::Skill(KeyValueFile *p_config)
{
	this->loadFromConfig(p_config);
}

Skill::~Skill(void)
{
}


//*************************************************************
// Getters - Setter
//*************************************************************
long Skill::getId()
{
	return this->mId;
}

void Skill::setId( long p_id )
{
	this->mId = p_id;
}

std::string Skill::getName()
{
	return this->mName;
}

void Skill::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string Skill::getDescription()
{
	return this->mDescription;
}

void Skill::setDescription( std::string p_description )
{
	this->mDescription = p_description;
}

std::string Skill::getSpriteId()
{
	return this->mSpriteId;
}

void Skill::setSpriteId( std::string p_id )
{
	this->mSpriteId = p_id;
}


//*************************************************************
// Methods
//*************************************************************
void Skill::loadFromConfig( KeyValueFile *p_config )
{
	this->setId(p_config->getInt(SKILL_CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(SKILL_CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(SKILL_CONFIG_DESCRIPTION)));
	this->setSpriteId(p_config->getString(SKILL_CONFIG_SPRITEID));
}

