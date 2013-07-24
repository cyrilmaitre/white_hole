#include "Job.h"


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
long Job::getId()
{
	return this->mId;
}

void Job::setId( long p_id )
{
	this->mId = p_id;
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
	this->setId(p_config->getLong(JOB_CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(JOB_CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(JOB_CONFIG_DESCRIPTION)));
	this->setSpriteId(p_config->getString(JOB_CONFIG_SPRITEID));
	this->setBonusSkill(p_config->getString(JOB_CONFIG_BONUS));
}
