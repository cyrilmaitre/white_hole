#pragma once
#include "ProgressBar.h"
#include "ItemStock.h"

class MarketItemStockBar : public ProgressBar
{
public:
	// Constructor - Destructor
	MarketItemStockBar(void);
	~MarketItemStockBar(void);

	// Getters - Setters
	ItemStock* getItemStock();
	void setItemStock(ItemStock* p_stock);

	// Methods
	void update();
	void updateStockMiniShapePosition();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyItemStockChanged();
	void notifyItemStockCurrentChanged();


private:
	// Attributs
	ItemStock* mItemStock;
	sf::RectangleShape mStockMiniShape;
};

