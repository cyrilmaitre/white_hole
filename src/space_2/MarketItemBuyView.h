#pragma once
#include "FieldSet.h"
#include "ItemStock.h"
#include "TextBox.h"
#include "TextField.h"
#include "DropDownList.h"
#include "Button.h"
#include "ItemStockSimulator.h"
#include "PopupBubble.h"
#include "WindowChoiceAction.h"

class MarketItemBuyView : public FieldSet, public WindowChoiceAction
{
public:
	// Constructor - Destructor
	MarketItemBuyView(void);
	~MarketItemBuyView(void);

	// Getters - Setters
	ItemStock* getItemStock();
	void setItemStock(ItemStock* p_stock);

	// Methods
	void buy();
	void buyConfirmation();
	void update();
	void updatePosition();
	void updateDestinations();
	void updateFieldsetTotalPosition();
	void updateFieldsetTotalSize();
	void updateFieldsetTotal();
	void checkQuantityValue();
	void update(sf::Event p_event);
	void draw();
	void notifyItemStockChanged();
	void notifyPositionChanged();
	void notifySizeChanged();
	void onButtonTrueClicked(WindowChoiceActionObject* p_object, std::string p_actionCommand);
	void onButtonFalseClicked(WindowChoiceActionObject* p_object, std::string p_actionCommand);
		

private:
	// Attributs
	ItemStock* mItemStock;
	ItemStockSimulator mItemStockSimulator;
	TextBox mTBQuantity;
	TextField mTFQuantity;
	Button mButtonQuantityAll;
	TextBox mTBDestination;
	DropDownList mDDLDestination;
	FieldSet mFieldsetTotal;
	TextBox mTBTotalLabel;
	TextBox mTBTotal;
	TextBox mTBTotalAverage;
	PopupBubble mPUBTotalDetail;
	Button mButtonBuy;

	mks::Clock mUpdateClock;
};

