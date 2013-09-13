#include "ItemFactory.h"


//*************************************************************
// Static init
//*************************************************************
ItemFactory* ItemFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
ItemFactory::ItemFactory(void)
{
}


ItemFactory::~ItemFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
Item * ItemFactory::getItem( std::string p_config, bool p_useLoaded)
{
	Item* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_config);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new Item(Resource::resource->getConfig(p_config));

		if(p_useLoaded)
			this->addObject(p_config, returnValue);

		return returnValue;
	}
}

Item* ItemFactory::getItem( KeyValueFile* p_config, bool p_useLoaded )
{
	Item* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_config->getFileName());

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new Item(p_config);

		if(p_useLoaded)
			this->addObject(p_config->getFileName(), returnValue);

		return returnValue;
	}
}

Item * ItemFactory::getItem( int p_id, bool p_useLoaded )
{
	return ItemFactory::getItem(ITEM_CONFIG+Tools::buildStringWithLong(p_id), p_useLoaded);
}

std::vector<Item*> ItemFactory::getItemAll(bool p_useLoaded)
{
	std::vector<KeyValueFile*> configs = Resource::resource->getConfigs(ITEM_CONFIG);
	std::vector<Item*> returnVector;

	for(int i = 0; i < configs.size(); i++)
		returnVector.push_back(this->getItem(configs[i], p_useLoaded));

	return returnVector;
}

std::vector<Item*> ItemFactory::getItemList()
{
	return this->mItemList;
}

void ItemFactory::buildItemList()
{
	// Get all Items
	this->mItemList = this->getItemAll();

	// Add to ItemType
	for(int i = 0; i < this->mItemList.size(); i++)
	{
		Item* currentItem = this->mItemList[i];
		currentItem->getItemType()->addItem(currentItem);
	}
}


