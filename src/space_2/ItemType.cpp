#include "ItemType.h"
#include "ItemTypeFactory.h"
#include "FactoryGet.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ItemType::ItemType( KeyValueFile* p_config ) 
{
	this->loadFromConfig(p_config);
}

ItemType::~ItemType(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long ItemType::getId()
{
	return this->mId;
}

void ItemType::setId( long p_id )
{
	this->mId = p_id;
}

std::string ItemType::getName()
{
	return this->mName;
}

void ItemType::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string ItemType::getDescription()
{
	return this->mDescription;
}

void ItemType::setDescription( std::string p_description )
{
	this->mDescription = p_description;
}

ItemType * ItemType::getParent()
{
	return (ItemType*)this->NodeData::getParent();
}

long ItemType::getParentId()
{
	return this->mParentId;
}

void ItemType::setParentId( long p_id )
{
	this->mParentId = p_id;
}

std::string ItemType::getText()
{
	return this->getName();
}


//*************************************************************
// Getters - Setters
//*************************************************************
void ItemType::loadFromConfig( KeyValueFile* p_config )
{
	this->setId(p_config->getLong(ITEMTYPE_CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(ITEMTYPE_CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(ITEMTYPE_CONFIG_DESCRIPTION)));

	if(p_config->getString(ITEMTYPE_CONFIG_PARENT) != "NULL")
		this->setParentId(p_config->getInt(ITEMTYPE_CONFIG_PARENT));
	else
		this->setParentId(-1);
}



