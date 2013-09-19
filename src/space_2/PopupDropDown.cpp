#include "PopupDropDown.h"
#include "PopupManager.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR			sf::Color(25, 26, 28)
#define BORDERCOLOR				sf::Color(194, 194, 194)
#define BORDERSIZE				1
#define PADDING					5
#define SEPARATOR_HEIGHT		3
#define SEPARATOR_COLOR			sf::Color(255, 255, 255, 0)


//*************************************************************
// Constructor - Destructor
//*************************************************************
PopupDropDown::PopupDropDown(void) : ListSelectableGroup(false)
{
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);
	this->setSeparatorHeight(SEPARATOR_HEIGHT);
	this->setSeparatorColor(SEPARATOR_COLOR);
	this->setVisible(false);
}

PopupDropDown::~PopupDropDown(void)
{
	PopupManager::getInstance()->removePopup(this);
}


//*************************************************************
// Methods
//*************************************************************
void PopupDropDown::update( sf::Event p_event )
{
	ListSelectableGroup::update(p_event);
	if(!this->hasMouseOver() && p_event.type == sf::Event::MouseButtonReleased && this->isVisible())
		this->setVisible(false);
}

void PopupDropDown::notifyVisibleChanged()
{
	if(this->isVisible())
		PopupManager::getInstance()->addPopup(this);
	else
		PopupManager::getInstance()->removePopup(this);
}

void PopupDropDown::notifySelectionChanged()
{
	ListSelectableGroup::notifySelectionChanged();
	this->setVisible(false);
}
