#include "ScrollbarThumb.h"
#include "Manager.h"

//*************************************************************
// Define
//*************************************************************
#define THUMB_WIDTH				9
#define SPRITE_SIZE				11


//*************************************************************
// Constructor - Destructor
//*************************************************************
ScrollbarThumb::ScrollbarThumb()
{
	this->mScrollBarSprite = Manager::getInstance()->getConfig()->getSpriteParameterScrollbar();
	this->mOrientation = Scrollbar::ScrollBarOrientation::Vertical;
	this->mPositionMin = 0;
	this->mPositionMax = 0;
	this->mPositionOffset = 0;
	
	this->notifyOrientationChanged();
}

ScrollbarThumb::~ScrollbarThumb(void)
{
	if(this->mScrollBarSprite != NULL)
		delete this->mScrollBarSprite;
}


//*************************************************************
// Getters - Setters
//*************************************************************
void ScrollbarThumb::setX( double p_x, bool p_notify, bool p_updateOffset )
{
	if(this->mOrientation == Scrollbar::ScrollBarOrientation::Horizontal)
	{
		if(p_x < this->mPositionMin)
			p_x = mPositionMin;
		else if(p_x > mPositionMax)
			p_x = mPositionMax;
	}
	Object::setX(p_x, p_notify);

	if(!p_notify)
		this->updateSpritePosition();

	if(p_updateOffset && this->mOrientation == Scrollbar::ScrollBarOrientation::Horizontal)
		this->mPositionOffset = this->getX() - this->mPositionMin;	
}

void ScrollbarThumb::setY( double p_y, bool p_notify, bool p_updateOffset )
{
	if(this->mOrientation == Scrollbar::ScrollBarOrientation::Vertical)
	{
		if(p_y < this->mPositionMin)
			p_y = mPositionMin;
		else if(p_y > mPositionMax)
			p_y = mPositionMax;
	}
	Object::setY(p_y, p_notify);

	if(!p_notify)
		this->updateSpritePosition();

	if(p_updateOffset && this->mOrientation == Scrollbar::ScrollBarOrientation::Vertical)
		this->mPositionOffset = this->getY() - this->mPositionMin;
}

Scrollbar::ScrollBarOrientation ScrollbarThumb::getOrientation()
{
	return this->mOrientation;
}

void ScrollbarThumb::setOrientation( Scrollbar::ScrollBarOrientation p_orientation )
{
	if(this->mOrientation != p_orientation)
	{
		this->mOrientation = p_orientation;
		this->notifyOrientationChanged();
	}
}

double ScrollbarThumb::getPositionMin()
{
	return this->mPositionMin;
}

void ScrollbarThumb::setPositionMin( double p_min )
{
	this->mPositionMin = p_min;
}

bool ScrollbarThumb::isPositionMin()
{
	if(this->mOrientation == Scrollbar::ScrollBarOrientation::Horizontal)
		return this->getX() == this->mPositionMin;
	else
		return this->getY() == this->mPositionMin;
}

double ScrollbarThumb::getPositionMax()
{
	return this->mPositionMax;
}

void ScrollbarThumb::setPositionMax( double p_max )
{
	this->mPositionMax = p_max;
}

bool ScrollbarThumb::isPositionMax()
{
	if(this->mOrientation == Scrollbar::ScrollBarOrientation::Horizontal)
		return this->getX() == mPositionMax;
	else
		return this->getY() == mPositionMax;
}

double ScrollbarThumb::getPositionOffset()
{
	return this->mPositionOffset;
}

double ScrollbarThumb::getPositionOffsetPercent()
{
	return this->getPositionOffset() / (this->getPositionMax() - this->getPositionMin());
}

void ScrollbarThumb::setPositionOffset( double p_offset, bool p_notify )
{
	if(this->mPositionOffset != p_offset)
	{
		this->mPositionOffset = p_offset;
		if(this->mOrientation == Scrollbar::ScrollBarOrientation::Horizontal)
			this->setX(this->getPositionMin() + this->getPositionOffset(), p_notify, false);
		else
			this->setY(this->getPositionMin() + this->getPositionOffset(), p_notify, false);
	}
}


//*************************************************************
// Methods
//*************************************************************
void ScrollbarThumb::draw()
{
	if(this->isVisible())
	{
		Resource::resource->getApp()->draw(this->mThumbTop);
		if(this->mOrientation == Scrollbar::ScrollBarOrientation::Vertical)
		{
			int midThumbCount = ceil((float)((this->getHeight() - (2 * SPRITE_SIZE)) / (float)SPRITE_SIZE));
			for(int i = 0; i < midThumbCount; i++)
			{
				this->mThumbMid.setPosition(this->getX(), this->getY() + (i + 1) * SPRITE_SIZE);
				Resource::resource->getApp()->draw(this->mThumbMid);
			}
		}
		else
		{
			int midThumbCount = ceil((float)((this->getWidth() - (2 * SPRITE_SIZE)) / (float)SPRITE_SIZE));
			for(int i = 0; i < midThumbCount; i++)
			{
				this->mThumbMid.setPosition(this->getX() + (i + 1) * SPRITE_SIZE, this->getY());
				Resource::resource->getApp()->draw(this->mThumbMid);
			}
		}
		Resource::resource->getApp()->draw(this->mThumbBottom);

	}
}

void ScrollbarThumb::update(sf::Event p_event)
{
	if(this->isVisible())
	{
		Focusable::update(p_event);
		if(this->hasFocus())
		{
			if(this->mOrientation == Scrollbar::ScrollBarOrientation::Vertical)
				this->setY(EventManager::eventManager->getMousePositionUiLocal().y - this->getFocusOriginLocalY());
			else
				this->setX(EventManager::eventManager->getMousePositionUiLocal().x - this->getFocusOriginLocalX());
		}
	}
}

void ScrollbarThumb::notifyOrientationChanged()
{
	this->updateSprite();	
}

void ScrollbarThumb::notifyPositionChanged()
{
	Focusable::notifyPositionChanged();
	this->updateSpritePosition();
}

void ScrollbarThumb::notifySizeChanged()
{
	Focusable::notifySizeChanged();
	this->updateSprite();
}

void ScrollbarThumb::notifyMouseOverChanged()
{
	Focusable::notifyMouseOverChanged();
	this->updateSprite();
}

void ScrollbarThumb::notifyFocusChanged()
{
	Focusable::notifyFocusChanged();
	this->updateSprite();
}

void ScrollbarThumb::updateSprite()
{
	if(this->mOrientation == Scrollbar::ScrollBarOrientation::Vertical)
	{
		if(this->hasFocus())
		{
			this->mThumbTop = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_THUMB_UP_FOCUS);
			this->mThumbMid = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_THUMB_MID_FOCUS);
			this->mThumbBottom = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_THUMB_DOWN_FOCUS);
		}
		else if(this->mMouseOver)
		{
			this->mThumbTop = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_THUMB_UP_OVER);
			this->mThumbMid = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_THUMB_MID_OVER);
			this->mThumbBottom = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_THUMB_DOWN_OVER);
		}
		else
		{
			this->mThumbTop = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_THUMB_UP);
			this->mThumbMid = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_THUMB_MID);
			this->mThumbBottom = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_THUMB_DOWN);
		}	
	}
	else
	{
		if(this->hasFocus())
		{
			this->mThumbTop = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_THUMB_UP_FOCUS);
			this->mThumbMid = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_THUMB_MID_FOCUS);
			this->mThumbBottom = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_THUMB_DOWN_FOCUS);
		}
		else if(this->mMouseOver)
		{
			this->mThumbTop = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_THUMB_UP_OVER);
			this->mThumbMid = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_THUMB_MID_OVER);
			this->mThumbBottom = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_THUMB_DOWN_OVER);
		}
		else
		{
			this->mThumbTop = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_THUMB_UP);
			this->mThumbMid = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_THUMB_MID);
			this->mThumbBottom = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_THUMB_DOWN);
		}
	}
	this->updateSpritePosition();
}

void ScrollbarThumb::updateSpritePosition()
{
	this->mThumbTop.setPosition(this->getX(), this->getY());

	if(this->mOrientation == Scrollbar::ScrollBarOrientation::Vertical)		
		this->mThumbBottom.setPosition(this->getX(), this->getY() + this->getHeight() - SPRITE_SIZE);
	else
		this->mThumbBottom.setPosition(this->getX()+ this->getWidth() - SPRITE_SIZE, this->getY());
}


