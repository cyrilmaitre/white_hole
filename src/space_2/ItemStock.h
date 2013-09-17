#pragma once
#include "Item.h"
#include "Station.h"
#include "Clock.h"


class ItemStock
{
public:
	// Constructor - Destructor
	ItemStock(Item* p_item, Station* p_station);
	~ItemStock(void);

	// Getters - Setters
	Item* getItem();
	void setItem(Item* p_item);

	Station* getStation();
	void setStation(Station* p_station);

	float getStockMin();
	void setStockMin(float p_min);

	float getStockMax();
	void setStockMax(float p_max);

	float getStockCurrent();
	void setStockCurrent(float p_current);

	bool isStockCurrentChanged();
	void setStockCurrentChanged(bool p_value);

	float getProduction();
	void setProduction(float p_production);

	float getConsumption();
	void setConsumption(float p_consumption);

	float getIndice();

	// Methods
	void update();
	void notifyItemChanged();
	void notifyStockCurrentChanged();


private:
	// Attributs
	Item* mItem;
	Station* mStation;

	float mStockMin;
	float mStockMax;
	float mStockCurrent;
	bool mStockCurrentChanged;
	float mProduction;
	float mConsumption;

	mks::Clock mClock;
};

