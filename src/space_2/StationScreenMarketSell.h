#pragma once
#include "FieldSet.h"
#include "StationScreenMarket.h"
#include "Containerable.h"
#include "ContainerView.h"
#include "TextBox.h"
#include "Button.h"
#include "TextBoxMultiLine.h"


class StationScreenMarketSell : public FieldSet, public Containerable 
{
public:
	// Constructor - Destructor
	StationScreenMarketSell(StationScreenMarket* p_market);
	~StationScreenMarketSell(void);

	// Methods
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();


private:
	// Attributs
	StationScreenMarket* mScreenMarket;
	ContainerView mContainerView;
	TextBox mTBTotalLabel;
	TextBox mTBTotal;
	Button mButtonSell;
	TextBoxMultiLine mTBMLDetail;
};

