#pragma once
#include "Listable.h"
#include "Image.h"
#include "Item.h"
#include "TextBox.h"

// Define
#define MARKETITEMLISTVIEW_WIDTH		350

class MarketItemListView : public Listable
{
public:
	// Constructor - Destructor
	MarketItemListView(Item* p_item);
	~MarketItemListView(void);

	// Getters - Setters
	Item* getItem();
	void setItem(Item* p_item);

	// Methods
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifyItemChanged();
	void notifyPositionChanged();
	void notifySelectedChanged();


private:
	// Attributs
	Item* mItem;
	Image mIcon;
	TextBox mTBName;
	TextBox mTBTier;
};

