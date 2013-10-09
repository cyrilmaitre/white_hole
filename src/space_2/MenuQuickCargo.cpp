#include "MenuQuickCargo.h"
#include "SpriteParameterFactory.h"
#include "UserInterface.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MenuQuickCargo::MenuQuickCargo(void)
{
	this->setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon32X32(true)->getSpritePtr(IC_32X32_CARGO));
	this->mInfo->addLine(Resource::resource->getBundle()->getString("menuQuickCargo"));
}

MenuQuickCargo::~MenuQuickCargo(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void MenuQuickCargo::notifyItemClicked()
{
	UserInterface::mUserInterface->getWindowCargo()->setOpenSwitch();
}
