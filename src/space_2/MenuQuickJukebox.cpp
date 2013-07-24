#include "MenuQuickJukebox.h"
#include "SpriteParameterFactory.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MenuQuickJukebox::MenuQuickJukebox(void)
{
	this->setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon32X32(true)->getSpritePtr(IC_32X32_JUKEBOX));
	this->mInfo->addLine(Resource::resource->getBundle()->getString("menuQuickJukebox"));
}

MenuQuickJukebox::~MenuQuickJukebox(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void MenuQuickJukebox::notifyItemClicked()
{

}
