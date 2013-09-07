#include "WindowWarning.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowWarning::WindowWarning( std::string p_title, std::string p_message ) : WindowMessage(p_title, p_message, SpriteParameterFactory::getSpriteParameterIcon64X64(false), IC_64X64_WARNING, IC_16X16_MAIL)
{

}

WindowWarning::~WindowWarning(void)
{
}
