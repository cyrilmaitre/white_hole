#pragma once
#include "ItemStock.h"


class ItemStockSimulator
{
public:
	// Constructor - Destructor
	ItemStockSimulator(void);
	~ItemStockSimulator(void);

	// Getters - Setters
	ItemStock* getItemStock();
	void setItemStock(ItemStock* p_stock);

	int getBuyQuantity();
	float getBuyPrice();
	float getBuyPriceMin();
	float getBuyPriceMax();
	float getBuyPriceAve();

	int getSellQuantity();
	float getSellPrice();
	float getSellPriceMin();
	float getSellPriceMax();
	float getSellPriceAve();

	// Methods
	void computeBuyPrice(int p_quantity);
	void computeSellPrice(int p_quantity);


private:
	// Attributs
	ItemStock* mItemStock;
	
	int mBuyQuantity;
	float mBuyPrice;
	float mBuyPriceMin;
	float mBuyPriceMax;
	float mBuyPriceAve;

	int mSellQuantity;
	float mSellPrice;
	float mSellPriceMin;
	float mSellPriceMax;
	float mSellPriceAve;

	// Methods
	float getPriceWithStock(float p_stock);
};

