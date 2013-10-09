#include "WindowShip.h"


//*************************************************************
// Define
//*************************************************************
#define WINDOW_WIDTH		320
#define WINDOW_HEIGHT		150


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowShip::WindowShip(void)
{
	this->setContentWidth(WINDOW_WIDTH);
	this->setContentHeight(WINDOW_HEIGHT);
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_SHIP));

	this->setPositionMiddleScreen();
}

WindowShip::~WindowShip(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
CharacterShip* WindowShip::getCharacterShip()
{
	return this->mCharacterShip;
}

void WindowShip::setCharacterShip( CharacterShip* p_ship )
{
	if(this->mCharacterShip != p_ship)
	{
		this->mCharacterShip = p_ship;
		this->notifyCharacterShipChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void WindowShip::drawContent()
{

}

void WindowShip::notifyCharacterShipChanged()
{
	if(this->mCharacterShip != NULL)
	{
		this->setWindowTitle(this->mCharacterShip->getName());
	}
}

