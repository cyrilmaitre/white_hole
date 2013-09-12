#include "ItemTypeFactory.h"


//*************************************************************
// Init static
//*************************************************************
ItemTypeFactory* ItemTypeFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
ItemTypeFactory::ItemTypeFactory(void)
{
	this->mItemTypeTree = NULL;
}

ItemTypeFactory::~ItemTypeFactory(void)
{
	if(this->mItemTypeTree != NULL)
		delete this->mItemTypeTree;
}


//*************************************************************
// Methode
//*************************************************************
ItemType * ItemTypeFactory::getItemType( std::string p_configItemType, bool p_useLoaded )
{
	ItemType* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configItemType);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new ItemType(Resource::resource->getConfig(p_configItemType));

		if(p_useLoaded)
			this->addObject(p_configItemType, returnValue);

		return returnValue;
	}
}

ItemType* ItemTypeFactory::getItemType( KeyValueFile* p_config, bool p_useLoaded )
{
	ItemType* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_config->getFileName());

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new ItemType(p_config);

		if(p_useLoaded)
			this->addObject(p_config->getFileName(), returnValue);

		return returnValue;
	}
}

ItemType * ItemTypeFactory::getItemType( int p_id, bool p_useLoaded )
{
	return ItemTypeFactory::getItemType(ITEMTYPE_CONFIG+Tools::buildStringWithInt(p_id), p_useLoaded);
}

std::vector<ItemType*> ItemTypeFactory::getItemTypeAll(bool p_useLoaded)
{
	std::vector<KeyValueFile*> configs = Resource::resource->getConfigs(ITEMTYPE_CONFIG);
	std::vector<ItemType*> returnVector;

	for(int i = 0; i < configs.size(); i++)
		returnVector.push_back(this->getItemType(configs[i], p_useLoaded));

	return returnVector;
}

TreeData* ItemTypeFactory::getItemTypeTree()
{
	return this->mItemTypeTree;
}

std::vector<ItemType*> ItemTypeFactory::getItemTypeList()
{
	return this->mItemTypeList;
}

void ItemTypeFactory::buildItemTypeTree()
{
	// Set childs
	for(int i = 0; i < this->mItemTypeList.size(); i++)
	{
		if(this->mItemTypeList[i]->getParentId() != -1)
		{
			ItemType* currentParent = this->getItemType(this->mItemTypeList[i]->getParentId());
			currentParent->addChild(this->mItemTypeList[i]);
		}
	}

	// Set roots
	this->mItemTypeTree = new TreeData();
	for(int i = 0; i < this->mItemTypeList.size(); i++)
	{
		if(this->mItemTypeList[i]->isRoot())
			this->mItemTypeTree->addRoot(this->mItemTypeList[i]);
	}

	return;
}

void ItemTypeFactory::buildItemTypeList()
{
	this->mItemTypeList = this->getItemTypeAll();
}


