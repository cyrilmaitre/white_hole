#include "MenuQuickSystem.h"
#include "SpriteParameterFactory.h"
#include "UserInterface.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MenuQuickSystem::MenuQuickSystem(void)
{
	this->setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon32X32(true)->getSpritePtr(IC_32X32_SYSTEM));
	this->mInfo->addLine(Resource::resource->getBundle()->getString("menuQuickSystem"));
}

MenuQuickSystem::~MenuQuickSystem(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void MenuQuickSystem::notifyItemClicked()
{
	UserInterface::mUserInterface->getWindowSystem()->setOpenSwitch();
}
