#include "ItemType.h"
#include "ItemTypeFactory.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_ID				"id"
#define CONFIG_NAME				"name"
#define CONFIG_DESCRIPTION		"description"
#define CONFIG_ICON				"icon"
#define CONFIG_PARENT			"itemtype_parent"


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

std::string ItemType::getIconIndex()
{
	return this->mIconIndex;
}

void ItemType::setIconIndex( std::string p_index )
{
	this->mIconIndex = p_index;
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

std::string ItemType::getIcon()
{
	return this->getIconIndex();
}

SpriteParameter* ItemType::getIconSprite()
{
	return SpriteParameterFactory::getSpriteParameterItemTypes();
}

int ItemType::getItemCount()
{
	return this->mItems.size();
}

Item* ItemType::getItem( int p_index )
{
	if(p_index < 0)
		p_index = 0;
	else if(p_index >= this->getItemCount())
		p_index = this->getItemCount() - 1;

	return this->mItems[p_index];
}


//*************************************************************
// Getters - Setters
//*************************************************************
void ItemType::addItem( Item* p_item, bool p_orderAlphabetically )
{
	if(p_orderAlphabetically)
	{
		bool inserted = false;
		for(int i = 0; i < this->mItems.size(); i++)
		{
			std::string newItemName = p_item->getName();
			std::string currentItemName = this->mItems[i]->getName();
			int compareResult = newItemName.compare(currentItemName); 
			if( compareResult < 0 || compareResult == 0)
			{
				this->mItems.insert(this->mItems.begin() + i, p_item);
				inserted = true;
				break;
			}
		}

		if(!inserted)
			this->mItems.push_back(p_item);
	}
	else
	{
		this->mItems.push_back(p_item);
	}
}

void ItemType::removeItem( Item* p_item )
{
	for(int i = 0; i < this->mItems.size(); i++)
	{
		if(p_item->getId() == this->mItems[i]->getId())
		{
			this->mItems.erase(this->mItems.begin() + i);
			break;
		}
	}
}

void ItemType::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_ID))
		this->setId(p_config->getLong(CONFIG_ID));
	
	if(p_config->has(CONFIG_NAME))
		this->setName(Resource::resource->getBundle()->getString(p_config->getString(CONFIG_NAME)));

	if(p_config->has(CONFIG_DESCRIPTION))
		this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(CONFIG_DESCRIPTION)));
	
	if(p_config->has(CONFIG_ICON))
		this->setIconIndex(p_config->getString(CONFIG_ICON));

	if(p_config->has(CONFIG_PARENT) && p_config->getString(CONFIG_PARENT) != "NULL")
		this->setParentId(p_config->getInt(CONFIG_PARENT));
	else
		this->setParentId(-1);
}








