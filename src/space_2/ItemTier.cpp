#include "ItemTier.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ItemTier::ItemTier( KeyValueFile* p_config )
{
	this->loadFromConfig(p_config);
}

ItemTier::~ItemTier(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long ItemTier::getId()
{
	return this->mId;
}

void ItemTier::setId(long p_id)
{
	this->mId = p_id;
}

std::string ItemTier::getName()
{
	return this->mName;
}

void ItemTier::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string ItemTier::getDescription()
{
	return this->mDescription;
}

void ItemTier::setDescription( std::string p_description )
{
	this->mDescription = p_description;
}


//*************************************************************
// Methode
//*************************************************************
void ItemTier::loadFromConfig( KeyValueFile* p_config )
{
	this->setId(p_config->getLong(ITEMTIER_CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(ITEMTIER_CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(ITEMTIER_CONFIG_DESCRIPTION)));
}
