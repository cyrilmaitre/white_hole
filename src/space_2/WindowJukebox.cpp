#include "WindowJukebox.h"


//*************************************************************
// Define
//*************************************************************
#define UIWINDOW_JUKEBOX_WIDTH		400
#define UIWINDOW_JUKEBOX_HEIGHT		300


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowJukebox::WindowJukebox(void)
{
	this->setContentWidth(UIWINDOW_JUKEBOX_WIDTH);
	this->setContentHeight(UIWINDOW_JUKEBOX_HEIGHT);
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowTitle(Resource::resource->getBundle()->getString("windowsTitleJuckebox"));
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_MUSIC));

	this->setPositionMiddleScreen();
}

WindowJukebox::~WindowJukebox(void)
{
}


//*************************************************************
// Methode
//*************************************************************
void WindowJukebox::drawContent()
{

}