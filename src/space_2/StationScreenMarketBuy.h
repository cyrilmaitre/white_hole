#pragma once
#include "FieldSet.h"
#include "StationScreenMarket.h"


class StationScreenMarketBuy : public FieldSet
{
public:
	// Constructor - Destructor
	StationScreenMarketBuy(StationScreenMarket* p_market);
	~StationScreenMarketBuy(void);

	// Methods
	void update();
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	StationScreenMarket* mScreenMarket;
};

