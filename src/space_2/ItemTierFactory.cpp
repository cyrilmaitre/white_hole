#include "ItemTierFactory.h"


//*************************************************************
// Init static
//*************************************************************
ItemTierFactory * ItemTierFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
ItemTierFactory::ItemTierFactory(void)
{
}

ItemTierFactory::~ItemTierFactory(void)
{
}


//*************************************************************
// Methode
//*************************************************************
ItemTier * ItemTierFactory::getItemTier( std::string p_configItemTier, bool p_useLoaded )
{
	ItemTier* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configItemTier);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new ItemTier(Resource::resource->getConfig(p_configItemTier));

		if(p_useLoaded)
			this->addObject(p_configItemTier, returnValue);

		return returnValue;
	}
}	

ItemTier * ItemTierFactory::getItemTier( int p_id, bool p_useLoaded )
{
	return ItemTierFactory::getItemTier(ITEMTIER_CONFIG+Tools::buildStringWithInt(p_id), p_useLoaded);
}
