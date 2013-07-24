#include "MenuQuickItem.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MenuQuickItem::MenuQuickItem(void) 
{
	this->setWidth(MENUQUICK_ITEM_WIDTH);
	this->setHeight(MENUQUICK_ITEM_HEIGHT);

	this->setBackgroundColor(MENUQUICK_ITEM_COLOR, true);
	this->setBorderSize(MENUQUICK_ITEM_BORDERSIZE, true);
	this->setBorderColor(MENUQUICK_ITEM_BORDERCOLOR);
	this->setBorderColorOver(MENUQUICK_ITEM_BORDERCOLOR);
	this->setBorderColorFocus(MENUQUICK_ITEM_BORDERCOLOR_FOCUS);

	this->mInfo = new PopupBubble(this);
}

MenuQuickItem::~MenuQuickItem(void)
{
	if(this->mInfo != NULL)
		delete this->mInfo;
}


//*************************************************************
// Methods
//*************************************************************
void MenuQuickItem::update(sf::Event p_event)
{
	Button::update(p_event);
	this->mInfo->update(p_event);
	if(this->isClicked())
		this->notifyItemClicked();
}

void MenuQuickItem::update()
{
	this->mInfo->update();
}

void MenuQuickItem::draw()
{
	Button::draw();
}
