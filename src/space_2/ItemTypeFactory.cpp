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
}

ItemTypeFactory::~ItemTypeFactory(void)
{
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

ItemType * ItemTypeFactory::getItemType( int p_id, bool p_useLoaded )
{
	return ItemTypeFactory::getItemType(ITEMTYPE_CONFIG+Tools::buildStringWithInt(p_id), p_useLoaded);
}
