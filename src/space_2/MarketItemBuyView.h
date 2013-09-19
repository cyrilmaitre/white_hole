#pragma once
#include "FieldSet.h"
#include "ItemStock.h"
#include "TextBox.h"
#include "TextField.h"
#include "DropDownList.h"
#include "Button.h"

class MarketItemBuyView : public FieldSet
{
public:
	// Constructor - Destructor
	MarketItemBuyView(void);
	~MarketItemBuyView(void);

	// Getters - Setters
	ItemStock* getItemStock();
	void setItemStock(ItemStock* p_stock);

	// Methods
	void update();
	void updatePosition();
	void updateDestinations();
	void checkQuantityValue();
	void update(sf::Event p_event);
	void draw();
	void notifyItemStockChanged();
	void notifyPositionChanged();
	void notifySizeChanged();
		

private:
	// Attributs
	ItemStock* mItemStock;
	TextBox mTBQuantity;
	TextField mTFQuantity;
	Button mButtonQuantityAll;
	TextBox mTBDestination;
	DropDownList mDDLDestination;
};

