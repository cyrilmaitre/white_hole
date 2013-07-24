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

Item * ItemFactory::getItem( int p_id, bool p_useLoaded )
{
	return ItemFactory::getItem(ITEM_CONFIG+Tools::buildStringWithLong(p_id), p_useLoaded);
}


