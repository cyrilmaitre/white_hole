#include "WindowMessageSuccess.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowMessageSuccess::WindowMessageSuccess( std::string p_title, std::string p_message ) : WindowMessage(p_title, p_message, SpriteParameterFactory::getSpriteParameterIcon64X64(false), IC_64X64_SUCCESS, IC_16X16_MAIL)
{

}


WindowMessageSuccess::~WindowMessageSuccess(void)
{
}
