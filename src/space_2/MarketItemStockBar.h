#pragma once
#include "ProgressBar.h"
#include "ItemStock.h"
#include "PopupBubble.h"

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
	void updateText();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyItemStockChanged();
	void notifyItemStockCurrentChanged();


private:
	// Attributs
	ItemStock* mItemStock;
	PopupBubble mPUBStock;
	sf::RectangleShape mStockMiniShape;
};

