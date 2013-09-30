#include "Skill.h"
#include "SkillFactory.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_ID				"id"
#define CONFIG_NAME				"name"
#define CONFIG_DESCRIPTION		"description"
#define CONFIG_SPRITEID			"spriteId"


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
long Skill::getIdSkill()
{
	return this->mIdSkill;
}

void Skill::setIdSkill( long p_id )
{
	this->mIdSkill = p_id;
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
	this->setIdSkill(p_config->getInt(CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(CONFIG_DESCRIPTION)));
	this->setSpriteId(p_config->getString(CONFIG_SPRITEID));
}

