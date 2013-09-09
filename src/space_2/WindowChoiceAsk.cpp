#include "WindowChoiceAsk.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowChoiceAsk::WindowChoiceAsk( std::string p_title, std::string p_message, WindowChoiceAction* p_actions, std::string p_actionCommand )
	: WindowChoice(p_title, p_message, SpriteParameterFactory::getSpriteParameterIcon64X64(false), IC_64X64_ASK, IC_16X16_MAIL, Resource::resource->getBundle()->getString("yes"), Resource::resource->getBundle()->getString("no"), p_actions, p_actionCommand)
{

}

WindowChoiceAsk::~WindowChoiceAsk(void)
{
}
