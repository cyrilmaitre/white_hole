#include "Object.h"
#include "View.h"

//*************************************************************
// Define
//*************************************************************
#define DEFAULT_POSITIONX		0
#define DEFAULT_POSITIONY		0
#define DEFAULT_WIDTH			1
#define DEFAULT_HEIGHT			1


//*************************************************************
// Init static
//*************************************************************
IdGenerator Object::mIdGenerator;


//*************************************************************
// Constructor - Destructor
//*************************************************************
Object::Object()
{
	this->mIdObject = Object::mIdGenerator.getNextId();
	this->mX = -1;
	this->mY = -1;
	this->mWidth = -1;
	this->mHeight = -1;

	this->setPosition(DEFAULT_POSITIONX, DEFAULT_POSITIONY);
	this->setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	
	this->mView = NULL;
	this->mVisible = true;
	this->mMouseOver = false;
	this->mMouseOverForced = false;
	this->mEnable = true;
	this->setUpdateMouseOver(true);

	this->mPositionChanged = false;
	this->mSizeChanged = false;
	this->mMouseOverChanged = false;
	this->mEnableChanged = false;
	this->mVisibleChanged = false;
}

Object::~Object( void )
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long Object::getIdObject()
{
	return this->mIdObject;
}

double Object::getX()
{
	return this->mX;
}

double Object::getX( Object *p_parentObject )
{
	return this->mX - p_parentObject->getX();
}

void Object::setX( double p_x, bool p_notify )
{
	if(this->mX != p_x)
	{
		this->mX = p_x;
		if(p_notify)
			this->notifyPositionChanged();
	}
}

void Object::setX( double p_x, Object *p_parentObject )
{
	this->setX(p_x + p_parentObject->getX());
}

double Object::getY()
{
	return this->mY;
}

double Object::getY( Object *p_parentObject )
{
	return this->mY - p_parentObject->getY();
}

void Object::setY( double p_y, bool p_notify )
{
	if(this->mY != p_y)
	{
		this->mY = p_y;
		if(p_notify)
			this->notifyPositionChanged();
	}
}

void Object::setY( double p_y, Object *p_parentObject )
{
	this->setY(p_y + p_parentObject->getY());
}

void Object::setPosition( double p_x, double p_y, bool p_notify)
{
	bool positionChanged = false;

	if(this->mX != p_x)
	{
		this->mX = p_x;
		positionChanged = true;
	}

	if(this->mY != p_y)
	{
		this->mY = p_y;
		positionChanged = true;
	}

	if(positionChanged && p_notify)
		this->notifyPositionChanged();
}

int Object::getWidth()
{
	return this->mWidth;
}

int Object::getWidthHalf()
{
	return this->getWidth() / 2;
}

void Object::setWidth( int p_witdh )
{
	if(this->mWidth != p_witdh)
	{
		this->mWidth = p_witdh;
		this->notifySizeChanged();
	}
}

int Object::getHeight()
{
	return this->mHeight;
}

int Object::getHeightHalf()
{
	return this->getHeight() / 2;
}

void Object::setHeight( int p_height )
{
	if(this->mHeight != p_height)
	{
		this->mHeight = p_height;
		this->notifySizeChanged();
	}
}

void Object::setSize( int p_witdh, int p_height )
{
	bool sizeChanged = false;

	if(this->mWidth != p_witdh)
	{
		this->mWidth = p_witdh;
		sizeChanged = true;
	}

	if(this->mHeight != p_height)
	{
		this->mHeight = p_height;
		sizeChanged = true;
	}

	if(sizeChanged)
		this->notifySizeChanged();
}

int Object::getArea()
{
	return this->mArea;
}

void Object::setArea( int p_area )
{
	this->mArea = p_area;
}

bool Object::isVisible()
{
	return this->mVisible;
}

void Object::setVisible( bool p_visible )
{
	if(this->mVisible != p_visible)
	{
		this->mVisible = p_visible;
		this->notifyVisibleChanged();
	}
}

bool Object::hasMouseOver()
{
	return this->mMouseOver;
}

bool Object::isMouseOverForced()
{
	return this->mMouseOverForced;
}

void Object::setMouseOverForced( bool p_forced )
{
	this->mMouseOverForced = p_forced;
}

bool Object::isUpdateMouseOver()
{
	return this->mUpdateMouseOver;
}

void Object::setUpdateMouseOver( bool p_param )
{
	this->mUpdateMouseOver = p_param;
}

View* Object::getView()
{
	return this->mView;
}

void Object::setView( View* p_view )
{
	if(this->mView != p_view)
	{
		if(this->mView != NULL)
			this->mView->removeObject(this);

		this->mView = p_view;

		if(this->mView != NULL)
			this->mView->addObject(this);
	}
}

bool Object::isEnable()
{
	return this->mEnable;
}

void Object::setEnable( bool p_enable )
{
	if(this->mEnable != p_enable)
	{
		this->mEnable = p_enable;
		this->notifyEnableChanged();
	}
}

bool Object::isPositionChanged()
{
	bool returnValue = this->mPositionChanged;
	this->mPositionChanged = false;
	return returnValue;
}

bool Object::isSizeChanged()
{
	bool returnValue = this->mSizeChanged;
	this->mSizeChanged = false;
	return returnValue;
}

bool Object::isMouseOverChanged()
{
	bool returnValue = this->mMouseOverChanged;
	this->mMouseOverChanged = false;
	return returnValue;
}

bool Object::isEnableChanged()
{
	bool returnValue = this->mEnableChanged;
	this->mEnableChanged = false;
	return returnValue;
}

bool Object::isVisibleChanged()
{
	bool returnValue = this->mVisibleChanged;
	this->mVisibleChanged = false;
	return returnValue;
}

double Object::getCenterX()
{
	return this->getX() + this->getWidth() / 2;
}

double Object::getLeftX()
{
	return this->mX;
}

double Object::getRightX()
{
	return this->mX + this->mWidth;
}

double Object::getCenterY()
{
	return this->getY() + this->getHeight() / 2;
}

double Object::getTopY()
{
	return this->mY;
}

double Object::getBottomY()
{
	return this->mY + this->mHeight;
}


//*************************************************************
// Methods
//*************************************************************
void Object::update(sf::Event p_event)
{
	if(this->isVisible())
	{
		if(this->isUpdateMouseOver())
			this->updateMouseOver();
	}
}

void Object::updateMouseOver()
{
	if(!EventManager::eventManager->isMouseOverEvent() || this->isMouseOverForced())
	{
		sf::Vector2i mousePosition = EventManager::eventManager->getMousePositionUiLocal();
		bool mouseOverChanged = false;
		if( Tools::pointOnObject(mousePosition.x, mousePosition.y, this->mX, this->mY, this->mX + this->mWidth, this->mY + this->mHeight) )
		{
			mouseOverChanged = !this->mMouseOver;
			this->mMouseOver = true;
			EventManager::eventManager->raiseMouseOverEvent();
		}
		else
		{
			mouseOverChanged = this->mMouseOver;
			this->mMouseOver = false;
		}

		if(mouseOverChanged)
			this->notifyMouseOverChanged();	
	}
	else
	{
		bool mouseOverChanged = this->mMouseOver;
		this->mMouseOver = false;
		if(mouseOverChanged)
			this->notifyMouseOverChanged();
	}
}

void Object::notifyPositionChanged()
{
	this->mPositionChanged = true;
}

void Object::notifySizeChanged()
{
	this->setArea(this->getWidth() * this->getHeight());
	this->mSizeChanged = true;
}

void Object::notifyMouseOverChanged()
{
	this->mMouseOverChanged = true;
}

void Object::notifyEnableChanged()
{
	this->mEnableChanged = true;
}

void Object::notifyVisibleChanged()
{
	this->mVisibleChanged = true;
}







