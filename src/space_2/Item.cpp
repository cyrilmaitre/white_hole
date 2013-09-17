#include "Item.h"
#include "FactoryGet.h"
#include "ItemFactory.h"
#include "Tools.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_ID					"id"
#define CONFIG_NAME					"name"
#define CONFIG_DESCRIPTION			"description"
#define CONFIG_PRICE				"price"
#define CONFIG_STACKMAX				"stackmax"
#define CONFIG_SPRITE				"sprite"
#define CONFIG_ITEMTYPE				"itemtype"
#define CONFIG_ITEMTIER				"itemtier"
#define CONFIG_BUYABLE				"buyable"
#define CONFIG_STOCKMINIMUMMIN		"stockminimum_min"
#define CONFIG_STOCKMINIMUMMAX		"stockminimum_max"
#define CONFIG_STOCKMAXIMUMMIN		"stockmaximum_min"
#define CONFIG_STOCKMAXIMUMMAX		"stockmaximum_max"
#define CONFIG_PRODUCTIONMIN		"production_min"
#define CONFIG_PRODUCTIONMAX		"production_max"
#define CONFIG_CONSUMPTIONMIN		"consumption_min"
#define CONFIG_CONSUMPTIONMAX		"consumption_max"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Item::Item( KeyValueFile *p_config ): mItemType(NULL), mItemTier(NULL)
{
	this->init();
	this->loadFromConfig(p_config);
}

Item::Item( int p_id ): mItemType(NULL), mItemTier(NULL)
{
	this->init();
	this->loadFromConfig(Resource::resource->getConfig(ITEM_CONFIG+Tools::buildStringWithLong(p_id)));
}

void Item::init()
{
	this->mBuyable = true;
	this->mStockMinimumMin = 0;
	this->mStockMinimumMax = 0;
	this->mStockMaximumMin = 0;
	this->mStockMaximumMax = 0;
	this->mProductionMin = 0;
	this->mProductionMax = 0;
	this->mConsumptionMin = 0;
	this->mConsumptionMax = 0;
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

bool Item::isBuyable()
{
	return this->mBuyable;
}

void Item::setBuyable( bool p_value )
{
	this->mBuyable = p_value;
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

float Item::getStockMinimumMin()
{
	return this->mStockMinimumMin;
}

void Item::setStockMinimumMin( float p_min )
{
	this->mStockMinimumMin = p_min;
}

float Item::getStockMinimumMax()
{
	return this->mStockMinimumMax;
}

void Item::setStockMinimumMax( float p_max )
{
	this->mStockMinimumMax = p_max;
}

float Item::getStockMaximumMin()
{
	return this->mStockMaximumMin;
}

void Item::setStockMaximumMin( float p_min )
{
	this->mStockMaximumMin = p_min;
}

float Item::getStockMaximumMax()
{
	return this->mStockMaximumMax;
}

void Item::setStockMaximumMax( float p_max )
{
	this->mStockMaximumMax = p_max;
}

float Item::getProductionMin()
{
	return this->mProductionMin;
}

void Item::setProductionMin( float p_min )
{
	this->mProductionMin = p_min;
}

float Item::getProductionMax()
{
	return this->mProductionMax;
}

void Item::setProductionMax( float p_max )
{
	this->mProductionMax = p_max;
}

float Item::getConsumptionMin()
{
	return this->mConsumptionMin;
}

void Item::setConsumptionMin( float p_min )
{
	this->mConsumptionMin = p_min;
}

float Item::getConsumptionMax()
{
	return this->mConsumptionMax;
}

void Item::setConsumptionMax( float p_max )
{
	this->mConsumptionMax = p_max;
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
	if(p_config->has(CONFIG_ID))
		this->setId(p_config->getLong(CONFIG_ID));

	if(p_config->has(CONFIG_NAME))
		this->setName(Resource::resource->getBundle()->getString(p_config->getString(CONFIG_NAME)));

	if(p_config->has(CONFIG_DESCRIPTION))
		this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(CONFIG_DESCRIPTION)));
	
	if(p_config->has(CONFIG_PRICE))
		this->setPrice(p_config->getDouble(CONFIG_PRICE));

	if(p_config->has(CONFIG_BUYABLE))
		this->setBuyable(p_config->getBool(CONFIG_BUYABLE));

	if(p_config->has(CONFIG_STACKMAX))
		this->setStackMax(p_config->getInt(CONFIG_STACKMAX));

	if(p_config->has(CONFIG_SPRITE))
		this->setSpriteId(p_config->getString(CONFIG_SPRITE));

	if(p_config->has(CONFIG_STOCKMINIMUMMIN))
		this->setStockMinimumMin(p_config->getFloat(CONFIG_STOCKMINIMUMMIN));

	if(p_config->has(CONFIG_STOCKMINIMUMMAX))
		this->setStockMinimumMax(p_config->getFloat(CONFIG_STOCKMINIMUMMAX));

	if(p_config->has(CONFIG_STOCKMAXIMUMMIN))
		this->setStockMaximumMin(p_config->getFloat(CONFIG_STOCKMAXIMUMMIN));

	if(p_config->has(CONFIG_STOCKMAXIMUMMAX))
		this->setStockMaximumMax(p_config->getFloat(CONFIG_STOCKMAXIMUMMAX));

	if(p_config->has(CONFIG_PRODUCTIONMIN))
		this->setProductionMin(p_config->getFloat(CONFIG_PRODUCTIONMIN));

	if(p_config->has(CONFIG_PRODUCTIONMAX))
		this->setProductionMax(p_config->getFloat(CONFIG_PRODUCTIONMAX));

	if(p_config->has(CONFIG_CONSUMPTIONMIN))
		this->setConsumptionMin(p_config->getFloat(CONFIG_CONSUMPTIONMIN));

	if(p_config->has(CONFIG_CONSUMPTIONMAX))
		this->setConsumptionMax(p_config->getFloat(CONFIG_CONSUMPTIONMAX));

	if(p_config->has(CONFIG_ITEMTYPE))
		this->setItemType(FactoryGet::getItemTypeFactory()->getItemType(p_config->getLong(CONFIG_ITEMTYPE)));

	if(p_config->has(CONFIG_ITEMTIER))
		this->setItemTier(FactoryGet::getItemTierFactory()->getItemTier(p_config->getLong(CONFIG_ITEMTIER)));
}

float Item::generateStockMin()
{
	return Tools::random(this->getStockMinimumMin(), this->getStockMinimumMax());
}

float Item::generateStockMax()
{
	return Tools::random(this->getStockMaximumMin(), this->getStockMaximumMax());
}

float Item::generateProduction()
{
	return Tools::random(this->getProductionMin(), this->getProductionMax());
}

float Item::generateConsumption()
{
	return Tools::random(this->getConsumptionMin(), this->getConsumptionMax());
}











