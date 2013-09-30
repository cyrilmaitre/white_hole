#include "Job.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_ID				"id"
#define CONFIG_NAME				"name"
#define CONFIG_DESCRIPTION		"description"
#define CONFIG_BONUS			"bonus"
#define CONFIG_SPRITEID			"spriteId"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Job::Job( KeyValueFile *p_config )
{
	this->loadFromConfig(p_config);
}

Job::~Job(void)
{
}


//*************************************************************
// Getters - Setter
//*************************************************************
long Job::getIdJob()
{
	return this->mIdJob;
}

void Job::setIdJob( long p_id )
{
	this->mIdJob = p_id;
}

std::string Job::getName()
{
	return this->mName;
}

void Job::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string Job::getDescription()
{
	return this->mDescription;
}

void Job::setDescription( std::string p_description )
{
	this->mDescription = p_description;
}

std::string Job::getSpriteId()
{
	return this->mSpriteId;
}

void Job::setSpriteId( std::string p_id )
{
	this->mSpriteId = p_id;
}


//*************************************************************
// Methods
//*************************************************************
void Job::loadFromConfig( KeyValueFile *p_config )
{
	this->setIdJob(p_config->getLong(CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(CONFIG_DESCRIPTION)));
	this->setSpriteId(p_config->getString(CONFIG_SPRITEID));
	this->setBonusSkill(p_config->getString(CONFIG_BONUS));
}
