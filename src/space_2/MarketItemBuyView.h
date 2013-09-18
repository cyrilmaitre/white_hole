#pragma once
#include "FieldSet.h"
#include "ItemStock.h"


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
	void update(sf::Event p_event);
	void draw();
	void notifyItemStockChanged();
	void notifyPositionChanged();
	void notifySizeChanged();
		

private:
	// Attributs
	ItemStock* mItemStock;
};

