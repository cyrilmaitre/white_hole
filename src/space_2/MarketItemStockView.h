#pragma once
#include "FieldSet.h"
#include "TextBox.h"
#include "ItemStock.h"
#include "PopupBubble.h"
#include "MarketItemStockBar.h"


class MarketItemStockView : public FieldSet
{
public:
	// Constructor - Destructor
	MarketItemStockView(void);
	~MarketItemStockView(void);

	// Getters - Setters
	ItemStock* getItemStock();
	void setItemStock(ItemStock* p_stock);

	void setIndice(float p_indice);

	// Methods
	void updatePosition();
	void update();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyItemStockChanged();


private:
	// Attributs
	ItemStock* mItemStock;
	TextBox mTBIndiceLabel;
	TextBox mTBIndice;
	PopupBubble mPUBIndice;
	MarketItemStockBar mStockBar;
};

