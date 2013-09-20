#pragma once
#include "Item.h"
#include "Station.h"
#include "Clock.h"
#include "IdGenerator.h"


class ItemStock
{
public:
	// Constructor - Destructor
	ItemStock(Item* p_item, Station* p_station);
	~ItemStock(void);

	// Getters - Setters
	long getId();

	Item* getItem();
	void setItem(Item* p_item);

	Station* getStation();
	void setStation(Station* p_station);

	long getStockMin();
	void setStockMin(long p_min);

	long getStockMax();
	void setStockMax(long p_max);

	float getStockCurrent();
	float getStockSpaceAvailable();
	void setStockCurrent(float p_current);

	bool isStockCurrentChanged();
	void setStockCurrentChanged(bool p_value);

	float getProduction();
	void setProduction(float p_production);

	float getConsumption();
	void setConsumption(float p_consumption);

	float getIndice();

	// Methods
	void incStockCurrent(float p_inc);
	void decStockCurrent(float p_dec);

	void update();
	void notifyItemChanged();
	void notifyStockCurrentChanged();


private:
	// Attributs
	long mId;
	Item* mItem;
	Station* mStation;

	long mStockMin;
	long mStockMax;
	float mStockCurrent;
	bool mStockCurrentChanged;
	float mProduction;
	float mConsumption;

	mks::Clock mClock;
	sf::Mutex mMutex;
	static IdGenerator mIdGenerator;
};

