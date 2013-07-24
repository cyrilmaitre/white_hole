#include "ItemType.h"
#include "ItemTypeFactory.h"
#include "FactoryGet.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ItemType::ItemType( KeyValueFile* p_config ) : mParent(NULL)
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
	return this->mParent;
}

void ItemType::setParent( ItemType *p_parent )
{
	this->mParent = p_parent;
}

bool ItemType::isLeaf()
{
	return this->mLeaf;
}

void ItemType::setLeaf( bool p_isleaf )
{
	this->mLeaf = p_isleaf;
}


//*************************************************************
// Getters - Setters
//*************************************************************
void ItemType::loadFromConfig( KeyValueFile* p_config )
{
	this->setId(p_config->getLong(ITEMTYPE_CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(ITEMTYPE_CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(ITEMTYPE_CONFIG_DESCRIPTION)));
	this->setLeaf(p_config->getBool(ITEMTYPE_CONFIG_LEAF));

	if(p_config->getString(ITEMTYPE_CONFIG_PARENT) == "NULL")
		this->setParent(NULL);
	else
		this->setParent(FactoryGet::getItemTypeFactory()->getItemType(p_config->getInt(ITEMTYPE_CONFIG_PARENT)));
}
