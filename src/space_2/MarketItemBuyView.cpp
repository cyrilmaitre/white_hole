#include "MarketItemBuyView.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR				sf::Color(25, 26, 28)
#define BORDERCOLOR					sf::Color(255, 255, 255, 0)
#define BORDERSIZE					0
#define PADDING						10


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarketItemBuyView::MarketItemBuyView(void)
{
	this->setVisible(false);
	this->setDisplayTitle(false);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);
}

MarketItemBuyView::~MarketItemBuyView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ItemStock* MarketItemBuyView::getItemStock()
{
	return this->mItemStock;
}

void MarketItemBuyView::setItemStock( ItemStock* p_stock )
{
	if(this->mItemStock != p_stock)
	{
		this->mItemStock = p_stock;
		this->notifyItemStockChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void MarketItemBuyView::update()
{

}

void MarketItemBuyView::update( sf::Event p_event )
{
	if(this->isVisible())
	{

	}
	FieldSet::update(p_event);
}

void MarketItemBuyView::updatePosition()
{

}

void MarketItemBuyView::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{

	}
}

void MarketItemBuyView::notifyItemStockChanged()
{
	this->setVisible(this->mItemStock != NULL);
}

void MarketItemBuyView::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
}

void MarketItemBuyView::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
}