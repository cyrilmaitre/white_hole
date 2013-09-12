#include "StationScreenMarket.h"
#include "StationScreenMarketBuy.h"
#include "StationScreenMarketSell.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
#define BUTTON_WIDTH				150
#define BUTTON_HEIGHT				25
#define BUTTON_MARGIN				10


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationScreenMarket::StationScreenMarket( Character* p_character, Station* p_station, StationScreen* p_screen ) : StationScreenRightPanel(p_character, p_station, p_screen)
{
	this->mScreenBuy = NULL;
	this->mScreenSell = NULL;

	this->setTitle(Resource::resource->getBundle()->getString("market"));
	this->setDisplayTitle(true);

	this->mScreenBuy = new StationScreenMarketBuy(this);
	this->mScreenSell = new StationScreenMarketSell(this);

	this->mButtonBuy.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	this->mButtonBuy.setTitle(Resource::resource->getBundle()->getString("buy"));

	this->mButtonSell.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	this->mButtonSell.setTitle(Resource::resource->getBundle()->getString("sell"));

	this->loadScreenBuy();
}

StationScreenMarket::~StationScreenMarket(void)
{
	delete this->mScreenBuy;
	delete this->mScreenSell;
}


//*************************************************************
// Getters - Setters
//*************************************************************
StationScreenMarketBuy* StationScreenMarket::getScreenBuy()
{
	return this->mScreenBuy;
}

StationScreenMarketSell* StationScreenMarket::getScreenSell()
{
	return this->mScreenSell;
}


//*************************************************************
// Methods
//*************************************************************
void StationScreenMarket::loadScreenBuy()
{
	this->mScreenSell->setVisible(false);
	this->mScreenBuy->setVisible(true);
}

void StationScreenMarket::loadScreenSell()
{
	this->mScreenSell->setVisible(true);
	this->mScreenBuy->setVisible(false);
}

void StationScreenMarket::update()
{
	if(this->mScreenBuy->isVisible())
		this->mScreenBuy->update();

	if(this->mScreenSell->isVisible())
		this->mScreenSell->update();
}

void StationScreenMarket::updatePosition()
{
	this->mButtonBuy.setPosition(this->getContentX(), this->getContentY());
	this->mButtonSell.setPosition(this->mButtonBuy.getRightX() + BUTTON_MARGIN, this->mButtonBuy.getY());

	this->mScreenBuy->setPosition(this->getContentX(), this->mButtonBuy.getBottomY() + BUTTON_MARGIN);
	this->mScreenSell->setPosition(this->getContentX(), this->mButtonBuy.getBottomY() + BUTTON_MARGIN);
}

void StationScreenMarket::update( sf::Event p_event )
{
	this->mButtonBuy.update(p_event);
	if(this->mButtonBuy.isClicked())
		this->loadScreenBuy();

	this->mButtonSell.update(p_event);
	if(this->mButtonSell.isClicked())
		this->loadScreenSell();

	if(this->mScreenBuy->isVisible())
		this->mScreenBuy->update(p_event);

	if(this->mScreenSell->isVisible())
		this->mScreenSell->update(p_event);

	FieldSet::update(p_event);
}

void StationScreenMarket::draw()
{
	FieldSet::draw();

	if(this->mScreenBuy->isVisible())
		this->mScreenBuy->draw();

	if(this->mScreenSell->isVisible())
		this->mScreenSell->draw();

	this->mButtonBuy.draw();
	this->mButtonSell.draw();
}

void StationScreenMarket::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
	this->mScreenBuy->setSize(this->getContentWidth(), this->getContentHeight() - BUTTON_HEIGHT - BUTTON_MARGIN);
	this->mScreenSell->setSize(this->getContentWidth(), this->getContentHeight() - BUTTON_HEIGHT - BUTTON_MARGIN);
}

void StationScreenMarket::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}






