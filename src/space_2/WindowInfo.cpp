#include "WindowInfo.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowInfo::WindowInfo( std::string p_title, std::string p_message ) : WindowMessage(p_title, p_message, SpriteParameterFactory::getSpriteParameterIcon64X64(false), IC_64X64_INFO, IC_16X16_MAIL)
{

}

WindowInfo::~WindowInfo(void)
{
}
