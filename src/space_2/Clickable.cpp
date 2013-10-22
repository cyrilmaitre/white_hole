#include "Clickable.h"

//******************************
// Constructor - Destructor
//******************************
Clickable::Clickable() 
{
	this->mClicked = false;
	this->setUpdateClicked(true);
}

Clickable::~Clickable(void)
{
}


//******************************
// Getters - Setters
//******************************
bool Clickable::isClicked()
{
	bool clickedValue = this->mClicked && this->isEnable();	
	this->mClicked = false;									
	return clickedValue;
}

void Clickable::setClicked( bool p_value )
{
	if(this->mClicked != p_value)
	{
		this->mClicked = p_value;
		this->notifyClickedChanged();
	}
}

bool Clickable::isUpdateClicked()
{
	return this->mUpdateClicked;
}

void Clickable::setUpdateClicked( bool p_param )
{
	this->mUpdateClicked = p_param;
}


//******************************
// Methods
//******************************
void Clickable::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		Focusable::update(p_event);
		if(this->isUpdateClicked())
			this->updateClicked(p_event);
	}
}

void Clickable::updateClicked( sf::Event p_event )
{
	if(p_event.type == sf::Event::MouseButtonReleased && p_event.mouseButton.button == sf::Mouse::Left)
	{
		if(this->mMouseOver)
			this->setClicked(true);
		else
			this->setClicked(false);
	}
	else
	{
		this->setClicked(false);
	}
}

void Clickable::notifyClickedChanged()
{

}


