#include "WindowMessageError.h"
#include "Jukebox.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
#define SOUND_ERROR		"windowError.ogg"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowMessageError::WindowMessageError( std::string p_title, std::string p_message ) : WindowMessage(p_title, p_message, SpriteParameterFactory::getSpriteParameterIcon64X64(false), IC_64X64_ERROR, IC_16X16_MAIL)
{
	Jukebox::getInstance()->playSound(SOUND_ERROR);
}

WindowMessageError::~WindowMessageError(void)
{
}
