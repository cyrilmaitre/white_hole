#include "MenuQuickChat.h"
#include "SpriteParameterFactory.h"
#include "Game.h"

//*************************************************************
// Constructor - Destructor
//*************************************************************
MenuQuickChat::MenuQuickChat(void)
{
	this->setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon32X32(true)->getSpritePtr(IC_32X32_CHAT));
	this->mInfo->addLine(Resource::resource->getBundle()->getString("menuQuickChat"));
}

MenuQuickChat::~MenuQuickChat(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void MenuQuickChat::notifyItemClicked()
{
		Game::game->getUserInterface()->getWindowChat()->setOpen(!Game::game->getUserInterface()->getWindowChat()->isOpen());
}
