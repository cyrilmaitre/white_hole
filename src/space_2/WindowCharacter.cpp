#include "WindowCharacter.h"


//*************************************************************
// Define
//*************************************************************
#define WINDOW_WIDTH		320
#define WINDOW_HEIGHT		150


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowCharacter::WindowCharacter(void)
{
	this->setContentWidth(WINDOW_WIDTH);
	this->setContentHeight(WINDOW_HEIGHT);
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_PERSON));

	this->setPositionMiddleScreen();
}

WindowCharacter::~WindowCharacter(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Character* WindowCharacter::getCharacter()
{
	return this->mCharacter;
}

void WindowCharacter::setCharacter( Character* p_character )
{
	if(this->mCharacter != p_character)
	{
		this->mCharacter = p_character;
		this->notifyCharacterChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void WindowCharacter::drawContent()
{

}

void WindowCharacter::notifyCharacterChanged()
{
	if(this->mCharacter != NULL)
	{
		this->setWindowTitle(this->mCharacter->getName());
	}
}
