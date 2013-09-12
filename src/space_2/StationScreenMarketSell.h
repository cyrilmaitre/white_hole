#pragma once
#include "FieldSet.h"
#include "StationScreenMarket.h"


class StationScreenMarketSell : public FieldSet
{
public:
	// Constructor - Destructor
	StationScreenMarketSell(StationScreenMarket* p_market);
	~StationScreenMarketSell(void);

	// Methods
	void update();
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	StationScreenMarket* mScreenMarket;
};

