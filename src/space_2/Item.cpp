#include "Item.h"
#include "FactoryGet.h"
#include "ItemFactory.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Item::Item( KeyValueFile *p_config ): mItemType(NULL), mItemTier(NULL)
{
	this->loadFromConfig(p_config);
}

Item::Item( int p_id ): mItemType(NULL), mItemTier(NULL)
{
	this->loadFromConfig(Resource::resource->getConfig(ITEM_CONFIG+Tools::buildStringWithLong(p_id)));
}

Item::~Item(void)
{
}


//*************************************************************
// Getters - Setter
//*************************************************************
long Item::getId()
{
	return this->mId;
}

void Item::setId( long p_id )
{
	this->mId = p_id;
}

std::string Item::getName()
{
	return this->mName;
}

void Item::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string Item::getDescription()
{
	return this->mDescription;
}

void Item::setDescription( std::string p_description )
{
	this->mDescription = p_description;
}

double Item::getPrice()
{
	return this->mPrice;
}

void Item::setPrice( double p_price )
{
	this->mPrice = p_price;
}

int Item::getStackMax()
{
	return this->mStackMax;
}

void Item::setStackMax( int p_max )
{
	this->mStackMax = p_max;
}

std::string Item::getSpriteId()
{
	return this->mSpriteId;
}

void Item::setSpriteId( std::string p_sprite )
{
	this->mSpriteId = p_sprite;
}

ItemType* Item::getItemType()
{
	return this->mItemType;
}

void Item::setItemType( ItemType *p_itemType )
{
	this->mItemType = p_itemType;
}

ItemTier* Item::getItemTier()
{
	return this->mItemTier;
}

void Item::setItemTier( ItemTier *p_itemTier )
{
	this->mItemTier = p_itemTier;
}


//*************************************************************
// Methode
//*************************************************************
void Item::loadFromConfig( KeyValueFile *p_config )
{
	this->setId(p_config->getLong(ITEM_CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(ITEM_CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(ITEM_CONFIG_DESCRIPTION)));
	this->setPrice(p_config->getDouble(ITEM_CONFIG_PRICE));
	this->setStackMax(p_config->getInt(ITEM_CONFIG_STACKMAX));
	this->setSpriteId(p_config->getString(ITEM_CONFIG_SPRITE));
	this->setItemType(FactoryGet::getItemTypeFactory()->getItemType(p_config->getLong(ITEM_CONFIG_ITEMTYPE)));
	this->setItemTier(FactoryGet::getItemTierFactory()->getItemTier(p_config->getLong(ITEM_CONFIG_ITEMTIER)));
}


