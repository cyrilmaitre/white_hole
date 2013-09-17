#include "ItemStock.h"
#include "Tools.h"


//*************************************************************
// Init static
//*************************************************************
IdGenerator ItemStock::mIdGenerator;


//*************************************************************
// Define
//*************************************************************
#define UPDATE_TICK				30 // Sec
#define DAY_DURATION			1440	


//*************************************************************
// Constructor - Destructor
//*************************************************************
ItemStock::ItemStock( Item* p_item, Station* p_station )
{
	this->mId = ItemStock::mIdGenerator.getNextId();
	this->mStockMin = 0;
	this->mStockMax = 0;
	this->mStockCurrent = 0;
	this->mStockCurrentChanged = false;
	this->mProduction = 0;
	this->mConsumption = 0;

	this->setItem(p_item);
	this->setStation(p_station);
}

ItemStock::~ItemStock(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long ItemStock::getId()
{
	return this->mId;
}

Item* ItemStock::getItem()
{
	return this->mItem;
}

void ItemStock::setItem( Item* p_item )
{
	if(this->mItem != p_item)
	{
		this->mItem = p_item;
		this->notifyItemChanged();
	}
}

Station* ItemStock::getStation()
{
	return this->mStation;
}

void ItemStock::setStation( Station* p_station )
{
	this->mStation = p_station;
}

float ItemStock::getStockMin()
{
	return this->mStockMin;
}

void ItemStock::setStockMin( float p_min )
{
	this->mStockMin = p_min;
}

float ItemStock::getStockMax()
{
	return this->mStockMax;
}

void ItemStock::setStockMax( float p_max )
{
	this->mStockMax = p_max;
}

float ItemStock::getStockCurrent()
{
	return this->mStockCurrent;
}

void ItemStock::setStockCurrent( float p_current )
{
	if(this->mStockCurrent != p_current)
	{
		this->mStockCurrent = p_current;
		this->notifyStockCurrentChanged();
	}
}

bool ItemStock::isStockCurrentChanged()
{
	bool returnValue = this->mStockCurrentChanged;
	this->mStockCurrentChanged = false;
	return returnValue;
}

void ItemStock::setStockCurrentChanged( bool p_value )
{
	this->mStockCurrentChanged = p_value;
}

float ItemStock::getProduction()
{
	return this->mProduction;
}

void ItemStock::setProduction( float p_production )
{
	this->mProduction = p_production;
}

float ItemStock::getConsumption()
{
	return this->mConsumption;
}

void ItemStock::setConsumption( float p_consumption )
{
	this->mConsumption = p_consumption;
}

float ItemStock::getIndice()
{
	return this->getProduction() - this->getConsumption();
}


//*************************************************************
// Methods
//*************************************************************
void ItemStock::update()
{
	if(this->mClock.getElapsedTimeAsSeconds() > UPDATE_TICK)
	{
		float stockVariation = this->getIndice() * (this->mClock.getElapsedTimeAsSeconds() / (float)DAY_DURATION);
		this->setStockCurrent(this->getStockCurrent() + stockVariation);
		this->mClock.restart();
	}
}

void ItemStock::notifyItemChanged()
{
	if(this->mItem != NULL)
	{
		this->setStockMin(this->getItem()->generateStockMin());
		this->setStockMax(this->getItem()->generateStockMax());
		this->setStockCurrent(Tools::random(0.f, this->getStockMax()));
		this->setProduction(this->getItem()->generateProduction());
		this->setConsumption(this->getItem()->generateConsumption());
	}
}

void ItemStock::notifyStockCurrentChanged()
{
	this->mStockCurrentChanged = true;
}





