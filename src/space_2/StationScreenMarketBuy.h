#pragma once
#include "FieldSet.h"
#include "StationScreenMarket.h"
#include "Tree.h"


class StationScreenMarketBuy : public FieldSet
{
public:
	// Constructor - Destructor
	StationScreenMarketBuy(StationScreenMarket* p_market);
	~StationScreenMarketBuy(void);

	// Methods
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	void notifySizeChanged();


private:
	// Attributs
	StationScreenMarket* mScreenMarket;
	Tree mTreeItemType;
};

