#include "ItemStockSimulator.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ItemStockSimulator::ItemStockSimulator(void)
{
	this->mItemStock = NULL;

	this->mBuyQuantity = 0;
	this->mBuyPrice = 0;
	this->mBuyPriceMin = 0;
	this->mBuyPriceMax = 0;
	this->mBuyPriceAve = 0;

	this->mSellQuantity = 0;
	this->mSellPrice = 0;
	this->mSellPriceMin = 0;
	this->mSellPriceMax = 0;
	this->mSellPriceAve = 0;
}

ItemStockSimulator::~ItemStockSimulator(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ItemStock* ItemStockSimulator::getItemStock()
{
	return this->mItemStock;
}

void ItemStockSimulator::setItemStock( ItemStock* p_stock )
{
	this->mItemStock = p_stock;
}

int ItemStockSimulator::getBuyQuantity()
{
	return this->mBuyQuantity;
}

float ItemStockSimulator::getBuyPrice()
{
	return this->mBuyPrice;
}

float ItemStockSimulator::getBuyPriceMin()
{
	return this->mBuyPriceMin;
}

float ItemStockSimulator::getBuyPriceMax()
{
	return this->mBuyPriceMax;
}

float ItemStockSimulator::getBuyPriceAve()
{
	return this->mBuyPriceAve;
}

int ItemStockSimulator::getSellQuantity()
{
	return this->mSellQuantity;
}

float ItemStockSimulator::getSellPrice()
{
	return this->mSellPrice;
}

float ItemStockSimulator::getSellPriceMin()
{
	return this->mSellPriceMin;
}

float ItemStockSimulator::getSellPriceMax()
{
	return this->mSellPriceMax;
}

float ItemStockSimulator::getSellPriceAve()
{
	return this->mSellPriceAve;
}

float ItemStockSimulator::getPriceWithStock( float p_stock )
{
	if(this->mItemStock->getStockMin() == p_stock)
		return this->mItemStock->getItem()->getPrice();
	else if(this->mItemStock->getStockMin() > p_stock)
		return this->mItemStock->getItem()->getPrice() * (1 + 1 - (p_stock / this->mItemStock->getStockMin()));
	else
		return this->mItemStock->getItem()->getPrice() / (1 + ((p_stock - this->mItemStock->getStockMin()) / (this->mItemStock->getStockMax() - this->mItemStock->getStockMin())));
}


//*************************************************************
// Methods
//*************************************************************
void ItemStockSimulator::computeBuyPrice( int p_quantity )
{
	if(this->mItemStock != NULL)
	{
		if(p_quantity < 0)
			p_quantity = 0;
		else if(p_quantity > this->mItemStock->getStockCurrent())
			p_quantity = this->mItemStock->getStockCurrent();
		this->mBuyQuantity = p_quantity;

		if(this->mBuyQuantity > 0)
		{
			int a = this->mItemStock->getStockCurrent() - p_quantity;
			int b = this->mItemStock->getStockCurrent();

			this->mBuyPriceMin = this->getPriceWithStock(b);
			this->mBuyPriceMax = this->getPriceWithStock(a + 1);

			if(b <= this->mItemStock->getStockMin() || (a >= this->mItemStock->getStockMin()))
			{
				this->mBuyPrice = (b - a) * ((this->mBuyPriceMax + this->mBuyPriceMin) / 2);
			}
			else
			{
				this->mBuyPrice =	(this->mItemStock->getStockMin() - a) * ((this->mBuyPriceMax + this->getPriceWithStock(this->mItemStock->getStockMin())) / 2) + 
									(b - this->mItemStock->getStockMin() + 1) * ((this->getPriceWithStock(this->mItemStock->getStockMin() + 2) + this->mBuyPriceMin) / 2);
			}
			this->mBuyPriceAve = this->mBuyPrice / this->mBuyQuantity;
		}
		else
		{
			this->mBuyPrice = 0;
			this->mBuyPriceMin = 0;
			this->mBuyPriceMax = 0;
			this->mBuyPriceAve = 0;
		}
	}
}

void ItemStockSimulator::computeSellPrice( int p_quantity )
{
	if(this->mItemStock != NULL)
	{
		if(p_quantity < 0)
			p_quantity = 0;
		else if(p_quantity > this->mItemStock->getStockSpaceAvailable())
			p_quantity = this->mItemStock->getStockSpaceAvailable();
		this->mSellQuantity = p_quantity;

		if(this->mSellQuantity > 0)
		{
			int a = this->mItemStock->getStockCurrent();
			int b = this->mItemStock->getStockCurrent() + p_quantity;

			this->mSellPriceMin = this->getPriceWithStock(b - 1);
			this->mSellPriceMax = this->getPriceWithStock(a);

			if(b <= this->mItemStock->getStockMin() || (a >= this->mItemStock->getStockMin()))
			{
				this->mSellPrice = (b - a) * ((this->mSellPriceMax + this->mSellPriceMin) / 2);
			}
			else
			{
				this->mSellPrice =	(this->mItemStock->getStockMin() - a) * ((this->mSellPriceMax + this->getPriceWithStock(this->mItemStock->getStockMin())) / 2) + 
									(b - this->mItemStock->getStockMin() + 1) * ((this->getPriceWithStock(this->mItemStock->getStockMin() + 2) + this->mSellPriceMin) / 2);
			}
			this->mSellPriceAve = this->mSellPrice / this->mSellQuantity;
		}
		else
		{
			this->mSellPrice = 0;
			this->mSellPriceMin = 0;
			this->mSellPriceMax = 0;
			this->mSellPriceAve = 0;
		}
	}
}


