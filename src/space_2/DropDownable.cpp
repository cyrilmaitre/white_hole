#include "DropDownable.h"

//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR				sf::Color(255, 255, 255, 0)
#define BACKGROUNDCOLOR_OVER		sf::Color(37, 37, 37)
#define BACKGROUNDCOLOR_SELECTED	sf::Color(90, 90, 90)


//*************************************************************
// Constructor - Destructor
//*************************************************************
DropDownable::DropDownable(void)
{
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBackgroundColorOver(BACKGROUNDCOLOR_OVER);
}

DropDownable::~DropDownable(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void DropDownable::notifySelectedChanged()
{

	Selectable::notifySelectedChanged();
	if(this->isSelected())
	{
		this->setBackgroundColor(BACKGROUNDCOLOR_SELECTED, true);
	}
	else
	{
		this->setBackgroundColor(BACKGROUNDCOLOR, true);
		this->setBackgroundColorOver(BACKGROUNDCOLOR_OVER);
	}
}
