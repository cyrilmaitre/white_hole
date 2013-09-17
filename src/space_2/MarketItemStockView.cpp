#include "MarketItemStockView.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR				sf::Color(25, 26, 28)
#define BORDERCOLOR					sf::Color(125, 125, 125)
#define BORDERSIZE					1
#define PADDING						10
#define LABEL_MARGIN				5
#define INDICE_POSITIVE_COLOR		sf::Color(0, 136, 0)
#define INDICE_NULL_COLOR			sf::Color(195,195,195)
#define INDICE_NEGATIVE_COLOR		sf::Color(238, 0, 0)


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarketItemStockView::MarketItemStockView() : mPUBIndice(&this->mTBIndice)
{
	this->mItemStock = NULL;
	
	this->setVisible(false);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);
	this->setDisplayTitle(false);

	this->mTBIndiceLabel.setText(Resource::resource->getBundle()->getString("marketBuyIndice"));
	this->setHeight(PADDING * 2 + this->mTBIndiceLabel.getHeight());
}

MarketItemStockView::~MarketItemStockView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ItemStock* MarketItemStockView::getItemStock()
{
	return this->mItemStock;
}

void MarketItemStockView::setItemStock( ItemStock* p_stock )
{
	if(this->mItemStock != p_stock)
	{
		this->mItemStock = p_stock;
		this->notifyItemStockChanged();
	}
}

void MarketItemStockView::setIndice( float p_indice )
{
	if(p_indice == 0)
	{
		this->mTBIndice.setFontColor(INDICE_NULL_COLOR);
		this->mTBIndice.setText("0");
	}
	else if(p_indice > 0)
	{
		this->mTBIndice.setFontColor(INDICE_POSITIVE_COLOR);
		this->mTBIndice.setText("+" + Tools::formatNumber(p_indice));
	}
	else
	{
		this->mTBIndice.setFontColor(INDICE_NEGATIVE_COLOR);
		this->mTBIndice.setText("-" + Tools::formatNumber(p_indice));
	}
}


//*************************************************************
// Methods
//*************************************************************
void MarketItemStockView::updatePosition()
{
	this->mTBIndiceLabel.setPosition(this->getContentX(), this->getContentY());
	this->mTBIndice.setPosition(this->mTBIndiceLabel.getRightX() + LABEL_MARGIN, this->mTBIndiceLabel.getY());
}

void MarketItemStockView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mTBIndice.update(p_event);
		this->mPUBIndice.update(p_event);
	}
	FieldSet::update(p_event);
}

void MarketItemStockView::update()
{
	if(this->isVisible())
	{
		this->mPUBIndice.update();
	}
}

void MarketItemStockView::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mTBIndiceLabel.draw();
		this->mTBIndice.draw();
	}
}

void MarketItemStockView::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}

void MarketItemStockView::notifyItemStockChanged()
{
	if(this->mItemStock != NULL)
	{
		this->setIndice(this->mItemStock->getIndice());
		this->mPUBIndice.clear(false);
		this->mPUBIndice.addLine(Resource::resource->getBundle()->getString("marketBuyIndicePerDay"));
		this->mPUBIndice.addLine(Resource::resource->getBundle()->getString("marketBuyProduction") + Tools::getSpaceAfterColon() + Tools::formatNumber(this->mItemStock->getProduction()));
		this->mPUBIndice.addLine(Resource::resource->getBundle()->getString("marketBuyConsumption") + Tools::getSpaceAfterColon() + Tools::formatNumber(this->mItemStock->getConsumption()));
	}
	this->setVisible(this->mItemStock != NULL);
}

