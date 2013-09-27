#pragma once
#include "FieldSet.h"
#include "StationScreenMarket.h"
#include "Containerable.h"
#include "ContainerView.h"
#include "TextBox.h"
#include "Button.h"
#include "TextBoxMultiLine.h"
#include "Clock.h"
#include "WindowChoiceAction.h"


class StationScreenMarketSell : public FieldSet, public Containerable, public WindowChoiceAction
{
public:
	// Constructor - Destructor
	StationScreenMarketSell(StationScreenMarket* p_market);
	~StationScreenMarketSell(void);

	// Methods
	void sell();
	void sellConfirmation();
	void update();
	void updatePosition();
	void updateTotalPosition();
	void updateTotal();
	void updateItemsCount();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	void onButtonTrueClicked(WindowChoiceActionObject* p_object, std::string p_actionCommand);
	void onButtonFalseClicked(WindowChoiceActionObject* p_object, std::string p_actionCommand);


private:
	// Attributs
	StationScreenMarket* mScreenMarket;
	ContainerView mContainerView;
	std::map<Item*, int> mContainerItemsCount;
	TextBox mTBTotalLabel;
	TextBox mTBTotal;
	Button mButtonSell;
	TextBoxMultiLine mTBMLDetail;

	mks::Clock mTotalClock;
};

