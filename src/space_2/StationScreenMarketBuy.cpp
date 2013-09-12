#include "StationScreenMarketBuy.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define PANEL_BACKCOLOR					sf::Color(255, 255, 255, 0)
#define PANEL_BORDCOLOR					sf::Color(128, 128, 128, 250)
#define PANEL_BORDSIZE					2
#define PANEL_TREEITEMTYPE_WIDTH		250


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationScreenMarketBuy::StationScreenMarketBuy( StationScreenMarket* p_market )
{
	this->mScreenMarket = p_market;

	this->setBackgroundColor(PANEL_BACKCOLOR, true);
	this->setBorderColor(PANEL_BORDCOLOR, true);
	this->setBorderSize(PANEL_BORDSIZE);
	this->setDisplayTitle(false);

	this->mTreeItemType.setSize(PANEL_TREEITEMTYPE_WIDTH, this->getContentHeight());
	this->mTreeItemType.setTreeData(FactoryGet::getItemTypeFactory()->getItemTypeTree());
}

StationScreenMarketBuy::~StationScreenMarketBuy(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
void StationScreenMarketBuy::update()
{

}

void StationScreenMarketBuy::updatePosition()
{
	this->mTreeItemType.setPosition(this->getContentX(), this->getContentY());
}

void StationScreenMarketBuy::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mTreeItemType.update(p_event);
	}
	FieldSet::update(p_event);
}

void StationScreenMarketBuy::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mTreeItemType.draw();
	}
}

void StationScreenMarketBuy::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this;updatePosition();
}

void StationScreenMarketBuy::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
	this->mTreeItemType.setHeight(this->getContentHeight());
}
