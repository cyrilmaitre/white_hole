#include "MenuQuickCharacter.h"
#include "SpriteParameterFactory.h"
#include "Game.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MenuQuickCharacter::MenuQuickCharacter(void)
{
	this->setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon32X32(true)->getSpritePtr(IC_32X32_CHARACTER));
	this->mInfo->addLine(Resource::resource->getBundle()->getString("menuQuickCharacter"));
}

MenuQuickCharacter::~MenuQuickCharacter(void)
{
}


//*************************************************************
// Methodes
//*************************************************************
void MenuQuickCharacter::notifyItemClicked()
{
	Game::game->getUserInterface()->getWindowCharacter()->setOpen(!Game::game->getUserInterface()->getWindowCharacter()->isOpen());
}
