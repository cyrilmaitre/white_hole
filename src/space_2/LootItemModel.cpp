#include "LootItemModel.h"
#include "FactoryGet.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
LootItemModel::LootItemModel( KeyValueFile* p_config )
{
	this->setItem(NULL);
	this->loadFromConfig(p_config);
}

LootItemModel::~LootItemModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long LootItemModel::getId()
{
	return this->mId;
}

void LootItemModel::setId( long p_id )
{
	this->mId = p_id;
}

Item* LootItemModel::getItem()
{
	return this->mItem;
}

void LootItemModel::setItem( Item* p_item )
{
	this->mItem = p_item;
}

int LootItemModel::getQuantityMin()
{
	return this->mQuantityMin;
}

void LootItemModel::setQuantityMin( int p_min )
{
	this->mQuantityMin = p_min;
}

int LootItemModel::getQuantityMax()
{
	return this->mQuantityMax;
}

void LootItemModel::setQuantityMax( int p_max )
{
	this->mQuantityMax = p_max;
}


//*************************************************************
// Methods
//*************************************************************
void LootItemModel::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(LOOTITEMMODEL_CONFIG_ID))
		this->setId(p_config->getLong(LOOTITEMMODEL_CONFIG_ID));

	if(p_config->has(LOOTITEMMODEL_CONFIG_ITEM))
		this->setItem(FactoryGet::getItemFactory()->getItem(p_config->getLong(LOOTITEMMODEL_CONFIG_ITEM)));

	if(p_config->has(LOOTITEMMODEL_CONFIG_QUANITYMIN))
		this->setQuantityMin(p_config->getInt(LOOTITEMMODEL_CONFIG_QUANITYMIN));

	if(p_config->has(LOOTITEMMODEL_CONFIG_QUANITYMAX))
		this->setQuantityMax(p_config->getInt(LOOTITEMMODEL_CONFIG_QUANITYMAX));
}

int LootItemModel::generateQuantity()
{
	return Tools::random(this->getQuantityMin(), this->getQuantityMax());
}
