#include "MenuQuickQuest.h"
#include "SpriteParameterFactory.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MenuQuickQuest::MenuQuickQuest(void)
{
	this->setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon32X32(true)->getSpritePtr(IC_32X32_QUEST));
	this->mInfo->addLine(Resource::resource->getBundle()->getString("menuQuickQuest"));
}

MenuQuickQuest::~MenuQuickQuest(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void MenuQuickQuest::notifyItemClicked()
{
	
}
