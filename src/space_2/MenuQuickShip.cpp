#include "MenuQuickShip.h"
#include "SpriteParameterFactory.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MenuQuickShip::MenuQuickShip(void)
{
	this->setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon32X32(true)->getSpritePtr(IC_32X32_CHARACTERSHIP));
	this->mInfo->addLine(Resource::resource->getBundle()->getString("menuQuickShip"));
}

MenuQuickShip::~MenuQuickShip(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void MenuQuickShip::notifyItemClicked()
{

}
