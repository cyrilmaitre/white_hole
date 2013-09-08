#include "WindowChoice.h"


//*************************************************************
// Define
//*************************************************************
#define BUTTON_WIDTH		150
#define BUTTON_HEIGHT		25
#define BUTTON_MARGIN		10


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowChoice::WindowChoice( std::string p_title, std::string p_message, SpriteParameter* p_spriteSheet, std::string p_spriteIndex, std::string p_windowIconIdex )
{
	this->updatePosition();
	this->updateMessageTextBox();
}


WindowChoice::~WindowChoice(void)
{
}
