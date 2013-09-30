#include "MarketItemStockBar.h"


//*************************************************************
// Define
//*************************************************************
#define STOCKBAR_BACKGROUNDCOLOR		sf::Color(25, 26, 28)
#define STOCKBAR_BORDERCOLOR			sf::Color(125, 125, 125)
#define STOCKBAR_BORDERSIZE				1
#define STOCKBAR_COLOR					sf::Color(75, 76, 78)
#define STOCKBAR_FONTCOLOR				sf::Color(195, 195, 195)
#define STOCKMINISHAPE_COLOR			sf::Color(127, 0, 0)
#define STOCKMINISHAPE_SIZE				3


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarketItemStockBar::MarketItemStockBar(void) : mPUBStock(this)
{
	this->mItemStock = NULL;

	this->setValueMin(0);
	this->setBackgroundColor(STOCKBAR_BACKGROUNDCOLOR, true);
	this->setBorderColor(STOCKBAR_BORDERCOLOR, true);
	this->setBorderSize(STOCKBAR_BORDERSIZE, true);
	this->setBarColor(STOCKBAR_COLOR);
	this->setFontColor(STOCKBAR_FONTCOLOR);

	this->mStockMiniShape.setFillColor(STOCKMINISHAPE_COLOR);
}

MarketItemStockBar::~MarketItemStockBar(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ItemStock* MarketItemStockBar::getItemStock()
{
	return this->mItemStock;
}

void MarketItemStockBar::setItemStock( ItemStock* p_stock )
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
void MarketItemStockBar::update()
{
	if(this->mItemStock != NULL && this->mItemStock->isStockCurrentChanged())
		this->notifyItemStockCurrentChanged();
	this->mPUBStock.update();
}

void MarketItemStockBar::updateText()
{
	//Update Text
	float currentStock = floor(this->mItemStock->getStockCurrent());
	if(currentStock > this->getValue())
		this->mText.setText(Tools::formatNumber((long)this->getValue()) + " (+" + Tools::formatNumber((long)(currentStock - this->getValue())) + ")" + " / " + Tools::formatNumber((long)this->getValueMax()));
	else
		this->mText.setText(Tools::formatNumber((long)this->getValue()) + " / " + Tools::formatNumber((long)this->getValueMax()));

	// Update PUB
	this->mPUBStock.clear(false);
	this->mPUBStock.addLine(Resource::resource->getBundle()->getString("marketBuyStock"));
	this->mPUBStock.addLine(Resource::resource->getBundle()->getString("marketBuyStockMin") + Tools::getSpaceAfterColon() + Tools::formatNumber(this->mItemStock->getStockMin()));
	this->mPUBStock.addLine(Resource::resource->getBundle()->getString("marketBuyStockMax") + Tools::getSpaceAfterColon() + Tools::formatNumber(this->mItemStock->getStockMax()));
	this->mPUBStock.addLine(Resource::resource->getBundle()->getString("marketBuyStockCurrent") + Tools::getSpaceAfterColon() + Tools::formatNumber(this->mItemStock->getStockCurrent()));

	// Update Position
	this->ProgressBar::updatePosition();
}

void MarketItemStockBar::updateStockMiniShapePosition()
{
	if(this->mItemStock != NULL)
	{
		float stockMiniPercent = (float)this->mItemStock->getStockMin() / (float)this->mItemStock->getStockMax();
		this->mStockMiniShape.setPosition(this->getX() + this->getWidth() * stockMiniPercent, this->getY());
	}
}

void MarketItemStockBar::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mPUBStock.update(p_event);
	}
	ProgressBar::update(p_event);
}

void MarketItemStockBar::draw()
{
	if(this->isVisible())
	{
		Block::draw();
		Resource::resource->getApp()->draw(this->mBar);
		Resource::resource->getApp()->draw(this->mStockMiniShape);
		this->mText.draw();
	}
}

void MarketItemStockBar::notifyPositionChanged()
{
	ProgressBar::notifyPositionChanged();
	this->updateStockMiniShapePosition();
}

void MarketItemStockBar::notifySizeChanged()
{
	ProgressBar::notifySizeChanged();
	this->mStockMiniShape.setSize(sf::Vector2f(STOCKMINISHAPE_SIZE, this->getHeight()));
	this->mStockMiniShape.setOrigin(this->mStockMiniShape.getSize().x / 2, 0);
	this->updateStockMiniShapePosition();
}

void MarketItemStockBar::notifyItemStockChanged()
{
	if(this->mItemStock != NULL)
	{
		this->setValueMax(this->mItemStock->getStockMax());
		this->setValue(floor(this->mItemStock->getStockCurrent()));
		this->updateStockMiniShapePosition();
		this->updateText();
	}
	this->setVisible(this->mItemStock != NULL);
}

void MarketItemStockBar::notifyItemStockCurrentChanged()
{
	this->setValue(floor(this->mItemStock->getStockCurrent()));
	this->updateText();
}