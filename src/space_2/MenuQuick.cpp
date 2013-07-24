#include "MenuQuick.h"
#include "MenuQuickCharacter.h"
#include "MenuQuickShip.h"
#include "MenuQuickCargo.h"
#include "MenuQuickQuest.h"
#include "MenuQuickChat.h"
#include "MenuQuickJukebox.h"
#include "MenuQuickSystem.h"
#include "MenuQuickMap.h"
#include "UserInterface.h"


//*************************************************************
// Define
//*************************************************************
#define MENUQUICK_FIRSTX			4
#define MENUQUICK_FIRSTY			-135
#define MENUQUICK_OFFSETX			34
#define ITEM_COLUMN_COUNT			2
#define ITEM_LINE_COUNT				4
#define ITEM_LINE_HEIGHT			34


//*************************************************************
// Constructor - Destructor
//*************************************************************
MenuQuick::MenuQuick(void)
{
	this->mMenuItem[0] = new MenuQuickCharacter();
	this->mMenuItem[1] = new MenuQuickShip();
	this->mMenuItem[2] = new MenuQuickCargo();
	this->mMenuItem[3] = new MenuQuickMap();
	this->mMenuItem[4] = new MenuQuickQuest();
	this->mMenuItem[5] = new MenuQuickChat();
	this->mMenuItem[6] = new MenuQuickJukebox();
	this->mMenuItem[7] = new MenuQuickSystem();

	this->updatePosition();
}

MenuQuick::~MenuQuick(void)
{
	for(int i = 0; i < MENUQUICK_ITEM_COUNT; i++)
	{
		if(this->mMenuItem[i] != NULL)
			delete this->mMenuItem[i];
	}
}


//*************************************************************
// Methods
//*************************************************************
void MenuQuick::update(sf::Event p_event)
{
	for(int i = 0; i < MENUQUICK_ITEM_COUNT; i++)
	{
		this->mMenuItem[i]->update(p_event);
	}
}

void MenuQuick::update()
{
	for(int i = 0; i < MENUQUICK_ITEM_COUNT; i++)
	{
		this->mMenuItem[i]->update();
	}
}

void MenuQuick::updatePosition()
{
	for(int i = 0; i < MENUQUICK_ITEM_COUNT; i++)
	{
		this->mMenuItem[i]->setX(Resource::resource->getViewUi()->getSize().x / 2 + INTERFACEBOTTOM_WIDTH / 2 + MENUQUICK_FIRSTX + i % ITEM_COLUMN_COUNT * MENUQUICK_OFFSETX);
		this->mMenuItem[i]->setY(Resource::resource->getViewUi()->getSize().y + MENUQUICK_FIRSTY + (i / ITEM_COLUMN_COUNT) * ITEM_LINE_HEIGHT);
	}
}

void MenuQuick::draw()
{
	for(int i = 0; i < MENUQUICK_ITEM_COUNT; i++)
	{
		this->mMenuItem[i]->draw();
	}
}
