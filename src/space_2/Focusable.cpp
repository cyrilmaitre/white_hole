#include "Focusable.h"

//*************************************************************
// Constructor - Destructor
//*************************************************************
Focusable::Focusable()
{
	this->mFocus = false;
	this->mFocusOriginLocalX = -1;
	this->mFocusOriginLocalY = -1;
	this->mFocusOriginGlobalX = -1;
	this->mFocusOriginGlobalY = -1;
	this->mFocusChanged = false;
	this->setUpdateFocus(true);
}

Focusable::~Focusable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool Focusable::hasFocus()
{
	return this->mFocus;
}

int Focusable::getFocusOriginLocalX()
{
	if(this->hasFocus())
		return this->mFocusOriginLocalX;
	else
		return -1;
}

int Focusable::getFocusOriginLocalY()
{
	if(this->hasFocus())
		return this->mFocusOriginLocalY;
	else 
		return -1;
}

int Focusable::getFocusOriginGlobalX()
{
	if(this->hasFocus())
		return this->mFocusOriginGlobalX;
	else
		return -1;
}

int Focusable::getFocusOriginGlobalY()
{
	if(this->hasFocus())
		return this->mFocusOriginGlobalY;
	else
		return -1;
}

bool Focusable::isUpdateFocus()
{
	return this->mUpdateFocus;
}

void Focusable::setUpdateFocus( bool p_param )
{
	this->mUpdateFocus = p_param;
}

bool Focusable::isFocusChanged()
{
	bool returnValue = this->mFocusChanged;
	this->mFocusChanged = false;
	return returnValue;
}


//*************************************************************
// Methods
//*************************************************************
void Focusable::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		Object::update(p_event);
		if(this->isUpdateFocus())
			this->updateFocus(p_event);
	}
}

void Focusable::updateFocus( sf::Event p_event )
{
	bool focusChanged = false;
	if(p_event.type == sf::Event::MouseButtonPressed && p_event.mouseButton.button == sf::Mouse::Left)
	{
		if(this->mMouseOver)
		{
			if(!this->mFocus)
				focusChanged = true;

			this->mFocus = true;
			sf::Vector2i mousePosition = EventManager::eventManager->getMousePositionUiLocal();
			this->mFocusOriginGlobalX = mousePosition.x;
			this->mFocusOriginGlobalY = mousePosition.y;
			this->mFocusOriginLocalX = this->mFocusOriginGlobalX - this->getX();
			this->mFocusOriginLocalY = this->mFocusOriginGlobalY - this->getY();			
		}
	}	
	else
	{
		bool oldFocus = this->mFocus;
		this->mFocus = sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->mFocus;

		if(this->mFocus != oldFocus)
			focusChanged = true;
	}

	if(focusChanged)
		this->notifyFocusChanged();
}

void Focusable::notifyFocusChanged()
{
	this->mFocusChanged = true;
}
