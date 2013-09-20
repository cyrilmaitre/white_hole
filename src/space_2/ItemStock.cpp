#include "ItemStock.h"
#include "Tools.h"


//*************************************************************
// Init static
//*************************************************************
IdGenerator ItemStock::mIdGenerator;


//*************************************************************
// Define
//*************************************************************
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

long ItemStock::getStockMin()
{
	return this->mStockMin;
}

void ItemStock::setStockMin( long p_min )
{
	this->mStockMin = p_min;
}

long ItemStock::getStockMax()
{
	return this->mStockMax;
}

void ItemStock::setStockMax( long p_max )
{
	this->mStockMax = p_max;
}

float ItemStock::getStockCurrent()
{
	sf::Lock lock(this->mMutex);

	return this->mStockCurrent;
}

float ItemStock::getStockSpaceAvailable()
{
	sf::Lock lock(this->mMutex);

	return this->mStockMax - this->mStockCurrent;
}

void ItemStock::setStockCurrent( float p_current )
{
	sf::Lock lock(this->mMutex);

	if(p_current < 0)
		p_current = 0;
	else if(p_current > this->getStockMax())
		p_current = this->getStockMax();

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
	sf::Lock lock(this->mMutex);

	return this->mProduction;
}

void ItemStock::setProduction( float p_production )
{
	this->mProduction = p_production;
}

float ItemStock::getConsumption()
{
	sf::Lock lock(this->mMutex);

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
void ItemStock::incStockCurrent( float p_inc )
{
	this->setStockCurrent(this->mStockCurrent + p_inc);
}

void ItemStock::decStockCurrent( float p_dec )
{
	this->setStockCurrent(this->mStockCurrent - p_dec);
}

void ItemStock::update()
{
	float stockVariation = this->getIndice() * (this->mClock.getElapsedTimeAsSeconds() / (float)DAY_DURATION);
	this->mClock.restart();
	this->setStockCurrent(this->getStockCurrent() + stockVariation);
}

void ItemStock::notifyItemChanged()
{
	if(this->mItem != NULL)
	{
		this->setStockMin(this->getItem()->generateStockMin());
		this->setStockMax(this->getItem()->generateStockMax());
		this->setStockCurrent(Tools::random(0.f, (float)this->getStockMax()));
		this->setProduction(this->getItem()->generateProduction());
		this->setConsumption(this->getItem()->generateConsumption());
	}
}

void ItemStock::notifyStockCurrentChanged()
{
	this->mStockCurrentChanged = true;
}



