#pragma once
#include "FieldSet.h"
#include "Item.h"
#include "Image.h"
#include "TextBox.h"
#include "TextBoxMultiLine.h"

class MarketItemDetailView : public FieldSet
{
public:
	// Constructor - Destructor
	MarketItemDetailView(void);
	~MarketItemDetailView(void);

	// Getters - Setters
	Item* getItem();
	void setItem(Item* p_item);

	// Methods
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyItemChanged();


private:
	// Attributs
	Item* mItem;
	Image mIcon;
	TextBox mTBName;
	TextBox mTBTier;
	TextBox mTBArianeType;
	Button mButtonMoreInfo;
	TextBoxMultiLine mTBDescription;
	TextBox mTBPriceLabel;
	TextBox mTBPrice;
	TextBox mTBStackMaxLabel;
	TextBox mTBstackMax;
};

