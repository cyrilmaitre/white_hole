#include "LootItemModelFactory.h"


//*************************************************************
// Init static
//*************************************************************
LootItemModelFactory * LootItemModelFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
LootItemModelFactory::LootItemModelFactory(void)
{
}

LootItemModelFactory::~LootItemModelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
LootItemModel * LootItemModelFactory::getLootItemModel( std::string p_config, bool p_useLoaded )
{
	LootItemModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_config);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new LootItemModel(Resource::resource->getConfig(p_config));

		if(p_useLoaded)
			this->addObject(p_config, returnValue);

		return returnValue;
	}
}

LootItemModel * LootItemModelFactory::getLootItemModel( int p_id, bool p_useLoaded  )
{
	return LootItemModelFactory::getLootItemModel(LOOTITEMMODEL_CONFIG + Tools::buildStringWithInt(p_id), p_useLoaded);
}
