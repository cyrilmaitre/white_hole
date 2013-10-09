#include "MenuQuickMap.h"
#include "SpriteParameterFactory.h"
#include "UserInterface.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MenuQuickMap::MenuQuickMap(void)
{
	this->setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon32X32(true)->getSpritePtr(IC_32X32_MAP));
	this->mInfo->addLine(Resource::resource->getBundle()->getString("menuQuickMap"));
}

MenuQuickMap::~MenuQuickMap(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void MenuQuickMap::notifyItemClicked()
{
	UserInterface::mUserInterface->getWindowMap()->setOpenSwitch();
}
