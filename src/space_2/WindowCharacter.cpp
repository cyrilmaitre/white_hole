#include "WindowCharacter.h"


//*************************************************************
// Define
//*************************************************************
#define UIWINDOW_PLAYER_WIDTH		320
#define UIWINDOW_PLAYER_HEIGHT		150


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowCharacter::WindowCharacter(void)
{
	this->setContentWidth(UIWINDOW_PLAYER_WIDTH);
	this->setContentHeight(UIWINDOW_PLAYER_HEIGHT);
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_PERSON));

	this->setPositionMiddleScreen();
}

WindowCharacter::~WindowCharacter(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void WindowCharacter::drawContent()
{

}