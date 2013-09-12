#include "StationScreenMarketBuy.h"


//*************************************************************
// Define
//*************************************************************
#define PANEL_BACKCOLOR					sf::Color(255, 255, 255, 0)
#define PANEL_BORDCOLOR					sf::Color(128, 128, 128, 250)
#define PANEL_BORDSIZE					2


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

void StationScreenMarketBuy::update( sf::Event p_event )
{
	FieldSet::update(p_event);
}

void StationScreenMarketBuy::draw()
{
	FieldSet::draw();
}
