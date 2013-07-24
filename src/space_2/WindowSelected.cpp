#include "WindowSelected.h"
#include "CharacterShip.h"
#include "Game.h"


//*************************************************************
// Define
//*************************************************************
#define OFFSETX					50
#define WINDOW_Y				20
#define WINDOW_WIDTH			320
#define WINDOW_HEIGHT			160		


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
WindowSelected::WindowSelected(void)
{
	this->setX(UserInterface::mUserInterface->getWindowShipSmall()->getRightX() + OFFSETX);
	this->setY(WINDOW_Y);
	this->setContentWidth(WINDOW_WIDTH);
	this->setContentHeight(WINDOW_HEIGHT);
	this->setType(Window::WindowType::TypeStaticLeft);
	this->setOpen(true);
}

WindowSelected::~WindowSelected(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void WindowSelected::notifyPositionChanged()
{
	Window::notifyPositionChanged();
}

void WindowSelected::update( sf::Event p_event )
{
	Window::update(p_event);
}
