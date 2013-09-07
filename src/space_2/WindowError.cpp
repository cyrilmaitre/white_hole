#include "WindowError.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowError::WindowError( std::string p_title, std::string p_message ) : WindowMessage(p_title, p_message, SpriteParameterFactory::getSpriteParameterIcon64X64(false), IC_64X64_ERROR, IC_16X16_MAIL)
{

}

WindowError::~WindowError(void)
{
}
