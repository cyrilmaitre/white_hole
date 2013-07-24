#include "Scrollbar.h"
#include "ScrollbarThumb.h"
#include "Manager.h"

//*************************************************************
// Define
//*************************************************************
#define THUMB_SIZE_OFFSET			44
#define SCROLL_PERCENT				0.1
#define SPRITE_SIZE					22
#define BUTTON_SIZE					18
#define BUTTON_OFFSET				2
#define THUMB_WIDTH					18
#define THUMB_SIZE_MIN				24


//*************************************************************
// Constructor - Destructor
//*************************************************************
Scrollbar::Scrollbar( ScrollBarOrientation p_orientation )
{
	this->mScrollBarSprite = Manager::getInstance()->getConfig()->getSpriteParameterScrollbar();
	this->mScrollBarThumb = new ScrollbarThumb();

	this->setButtonScrollActionDelegated(false);
	this->setOffsetOnScroll(-1);

	this->mOrientation = p_orientation;
	if(this->mOrientation == ScrollBarOrientation::Vertical)
		this->mWidth = SCROLLBAR_WIDTH;
	else
		this->mHeight = SCROLLBAR_WIDTH;

	this->mButtonScrollUp.setSize(BUTTON_SIZE, BUTTON_SIZE);
	this->mButtonScrollUp.setBorderSize(0, true);

	this->mButtonScrollDown.setSize(BUTTON_SIZE, BUTTON_SIZE);
	this->mButtonScrollDown.setBorderSize(0, true);
	
	this->notifyOrientationChanged();
	this->notifyPositionChanged();
	this->notifySizeChanged();
}

Scrollbar::~Scrollbar(void)
{
	if(this->mScrollBarThumb != NULL)
		delete this->mScrollBarThumb;

	if(this->mScrollBarSprite != NULL)
		delete this->mScrollBarSprite;
}


//*************************************************************
// Getters - Setters
//*************************************************************
Button* Scrollbar::getButtonScrollUp()
{
	return &this->mButtonScrollUp;
}

Button* Scrollbar::getButtonScrollDown()
{
	return &this->mButtonScrollDown;
}

Scrollbar::ScrollBarOrientation Scrollbar::getOrientation()
{
	return this->mOrientation;
}

void Scrollbar::setOrientation( ScrollBarOrientation p_orientation )
{
	if(this->mOrientation != p_orientation)
	{
		int tmpWidth = this->getWidth();
		this->setWidth(this->getHeight());
		this->setHeight(tmpWidth);

		this->mOrientation = p_orientation;
		this->notifyOrientationChanged();
	}
}

int Scrollbar::getScrollAreaHeight()
{
	return this->mScrollAreaHeight;
}

void Scrollbar::setScrollAreaHeight( int p_size )
{
	if(this->mScrollAreaHeight != p_size)
	{
		this->mScrollAreaHeight = p_size;
		this->updateThumbSize();
		this->updateThumbPositionRange();
	}
}

int Scrollbar::getScrollOffsetInPx()
{
	return this->getScrollOffsetInPercent() * (this->mScrollAreaHeight - this->getHeight());
}

void Scrollbar::setScrollOffsetInPx( int p_offset, bool p_notify )
{
	this->setScrollOffsetInPercent((float)p_offset / (float)(this->mScrollAreaHeight - this->getHeight()), p_notify);
}

float Scrollbar::getScrollOffsetInPercent()
{
	return (float)this->getThumbPosition() / (float)(this->getThumbHeightMax() - this->getThumbHeight());
}

void Scrollbar::setScrollOffsetInPercent( float p_percent, bool p_notify )
{
	this->setThumbPosition((float)this->getThumbHeightRange() * p_percent, p_notify);
}

float Scrollbar::getAreaDisplayedPercent()
{
	float areaDisplayedPercentage =  (float)this->getHeight() / (float)this->getScrollAreaHeight();
	if(areaDisplayedPercentage > 1 || this->getScrollAreaHeight() <= 0)
		areaDisplayedPercentage = 1;
	return areaDisplayedPercentage;
}

int Scrollbar::getThumbHeight()
{
	int thumbSizeMax = this->getThumbHeightMax();
	float areaDisplayedPercentage =  this->getAreaDisplayedPercent();

	int tmpThumbHeight = 0;
	if(this->mOrientation == ScrollBarOrientation::Vertical)
		tmpThumbHeight = (int)((float)(this->getHeight() - THUMB_SIZE_OFFSET) * areaDisplayedPercentage);
	else
		tmpThumbHeight = (int)((float)(this->getWidth() - THUMB_SIZE_OFFSET) * areaDisplayedPercentage);

	if(tmpThumbHeight < THUMB_SIZE_MIN)
		tmpThumbHeight = THUMB_SIZE_MIN;

	return tmpThumbHeight;
}

int Scrollbar::getThumbHeightMax()
{
	if(this->mOrientation == ScrollBarOrientation::Vertical)
		return this->getHeight() - THUMB_SIZE_OFFSET;
	else
		return this->getWidth() - THUMB_SIZE_OFFSET;
}

int Scrollbar::getThumbHeightRange()
{
	return this->getThumbHeightMax() - this->getThumbHeight();
}

int Scrollbar::getThumbPosition()
{
	if(this->mOrientation == ScrollBarOrientation::Vertical)
		return this->mScrollBarThumb->getY() - this->getY() - SPRITE_SIZE;
	else
		return this->mScrollBarThumb->getX() - this->getX() - SPRITE_SIZE;
}

void Scrollbar::setThumbPosition( int p_position, bool p_notify )
{
	if(this->mOrientation == ScrollBarOrientation::Vertical)
		this->mScrollBarThumb->setY(this->getY() + SPRITE_SIZE + p_position, p_notify);
	else
		this->mScrollBarThumb->setX(this->getX() + SPRITE_SIZE + p_position, p_notify);
}

void Scrollbar::setScrollBarHeight( int p_size )
{
	if(this->mOrientation == ScrollBarOrientation::Vertical)
		this->setHeight(p_size);
	else
		this->setWidth(p_size);
}

bool Scrollbar::isThumbPositionChanged()
{
	return this->mScrollBarThumb->isPositionChanged();
}

int Scrollbar::getOffsetOnScroll()
{
	return this->mOffsetOnScroll;
}

void Scrollbar::setOffsetOnScroll( int p_offset )
{
	this->mOffsetOnScroll = p_offset;
}

bool Scrollbar::isUsefull()
{
	return this->getAreaDisplayedPercent() < 1;
}

bool Scrollbar::isButtonScrollActionDelegated()
{
	return this->mButtonScrollActionDelegated;
}

void Scrollbar::setButtonScrollActionDelegated( bool p_delegated )
{
	this->mButtonScrollActionDelegated = p_delegated;
}


//*************************************************************
// Methods
//*************************************************************
void Scrollbar::scrollUp()
{
	int offset = 0;
	if(this->getOffsetOnScroll() != -1)
		offset = ((float)this->getOffsetOnScroll() / (float)this->getScrollAreaHeight()) * (float)this->getThumbHeightMax();
	else
		offset = ((float)this->getThumbHeightRange() * SCROLL_PERCENT);
	
	this->setThumbPosition(this->getThumbPosition() - offset);
}

void Scrollbar::scrollDown()
{
	int offset = 0;
	if(this->getOffsetOnScroll() != -1)
		offset = ((float)this->getOffsetOnScroll() / (float)this->getScrollAreaHeight()) * (float)this->getThumbHeightMax();
	else
		offset = ((float)this->getThumbHeightRange() * SCROLL_PERCENT);

	this->setThumbPosition(this->getThumbPosition() + offset);
}

void Scrollbar::draw()
{
	if(this->isVisible())
	{
		this->drawTrack();
		this->mScrollBarThumb->draw();
		this->mButtonScrollUp.draw();
		this->mButtonScrollDown.draw();
	}
}

void Scrollbar::drawTrack()
{
	Resource::resource->getApp()->draw(this->mTrackTop);

	if(this->mOrientation == ScrollBarOrientation::Vertical)
	{
		int midTrackCount = ceil((float)(this->getHeight() - 2 * (float)SPRITE_SIZE) / SPRITE_SIZE);
		for(int i = 0; i < midTrackCount; i++)
		{
			this->mTrackMid.setPosition(this->getX(), this->getY() + ((i + 1) * SPRITE_SIZE));
			Resource::resource->getApp()->draw(this->mTrackMid);
		}
	}
	else
	{
		int midTrackCount = ceil((float)(this->getWidth() - 2 * SPRITE_SIZE) / (float)SPRITE_SIZE);
		for(int i = 0; i < midTrackCount; i++)
		{
			this->mTrackMid.setPosition(this->getX() + ((i + 1) * SPRITE_SIZE), this->getY());
			Resource::resource->getApp()->draw(this->mTrackMid);
		}
	}

	Resource::resource->getApp()->draw(this->mTrackBottom);
}

void Scrollbar::update( sf::Event myEvent )
{
	if(this->isVisible())
	{
		this->mScrollBarThumb->update(myEvent);
		this->mButtonScrollUp.update(myEvent);
		this->mButtonScrollDown.update(myEvent);
		Object::update(myEvent);

		if(!this->isButtonScrollActionDelegated() && this->mButtonScrollUp.isClicked())
			this->scrollUp();

		if(!this->isButtonScrollActionDelegated() && this->mButtonScrollDown.isClicked())
			this->scrollDown();
	}
}

void Scrollbar::notifySizeChanged()
{
	Object::notifySizeChanged();
	this->updateButtonPosition();
	this->updateThumbSize();
	this->updateThumbPositionRange();
}

void Scrollbar::notifyPositionChanged()
{
	Object::notifyPositionChanged();
	this->updateButtonPosition();
	this->updateSpritePosition();
	this->updateThumbPosition();
	this->updateThumbPositionRange();
}

void Scrollbar::notifyOrientationChanged()
{
	this->updateSprite();
	this->mScrollBarThumb->setOrientation(this->mOrientation);
}

void Scrollbar::updateButtonPosition()
{
	this->mButtonScrollUp.setX(this->getX() + BUTTON_OFFSET);
	this->mButtonScrollUp.setY(this->getY() + BUTTON_OFFSET);	

	if(this->mOrientation == ScrollBarOrientation::Vertical)
	{
		this->mButtonScrollDown.setX(this->getX() + BUTTON_OFFSET);
		this->mButtonScrollDown.setY(this->getY() + this->getHeight() - SPRITE_SIZE + BUTTON_OFFSET);
	}
	else
	{
		this->mButtonScrollDown.setX(this->getX() + this->getWidth() - SPRITE_SIZE + BUTTON_OFFSET);
		this->mButtonScrollDown.setY(this->getY() + BUTTON_OFFSET);
	}
}

void Scrollbar::updateThumbPosition()
{
	int thumbPositionX = -1;
	int thumbPositionY = -1;

	if(this->mOrientation == ScrollBarOrientation::Vertical)
	{
		thumbPositionX = this->getX();
		thumbPositionY = this->getY() + SPRITE_SIZE;
	}
	else
	{
		thumbPositionX = this->getX() + SPRITE_SIZE;
		thumbPositionY = this->getY();
	}

	this->mScrollBarThumb->setPosition(thumbPositionX, thumbPositionY);
}

void Scrollbar::updateThumbPositionRange()
{
	int thumbPositionMin = -1;
	int thumbPositionMax = -1;

	if(this->mOrientation == ScrollBarOrientation::Vertical)
	{
		thumbPositionMin = this->getY() + SPRITE_SIZE;
		thumbPositionMax = this->getY() + this->getHeight() - SPRITE_SIZE - this->getThumbHeight(); 
	}
	else
	{
		thumbPositionMin = this->getX() + SPRITE_SIZE;
		thumbPositionMax = this->getX() + this->getWidth() - SPRITE_SIZE - this->getThumbHeight();
	}

	this->mScrollBarThumb->setPositionMin(thumbPositionMin);
	this->mScrollBarThumb->setPositionMax(thumbPositionMax);
}

void Scrollbar::updateThumbSize()
{
	int thumbWidth = -1;
	int thumbHeight = -1;

	if(this->mOrientation == ScrollBarOrientation::Vertical)
	{
		thumbWidth = THUMB_WIDTH;
		thumbHeight = this->getThumbHeight();
	}
	else
	{
		thumbWidth = this->getThumbHeight();
		thumbHeight = THUMB_WIDTH;
	}
	
	this->mScrollBarThumb->setSize(thumbWidth, thumbHeight);
}

void Scrollbar::updateSprite()
{
	if(this->mOrientation == ScrollBarOrientation::Vertical)
	{
		this->mButtonScrollUp.setBackgroundImage(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_V_BUTTON_UP), false);
		this->mButtonScrollUp.setBackgroundImageFocus(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_V_BUTTON_UP_OVER), false);
		this->mButtonScrollUp.setBackgroundImageOver(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_V_BUTTON_UP_FOCUS), false);

		this->mButtonScrollDown.setBackgroundImage(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_V_BUTTON_DOWN), false);
		this->mButtonScrollDown.setBackgroundImageFocus(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_V_BUTTON_DOWN_OVER), false);
		this->mButtonScrollDown.setBackgroundImageOver(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_V_BUTTON_DOWN_FOCUS), false);

		this->mTrackTop = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_TACK_UP);
		this->mTrackMid = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_TACK_MID);
		this->mTrackBottom = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_V_TACK_DOWN);
	}
	else
	{
		this->mButtonScrollUp.setBackgroundImage(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_H_BUTTON_UP), false);
		this->mButtonScrollUp.setBackgroundImageFocus(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_H_BUTTON_UP_OVER), false);
		this->mButtonScrollUp.setBackgroundImageOver(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_H_BUTTON_UP_FOCUS), false);

		this->mButtonScrollDown.setBackgroundImage(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_H_BUTTON_DOWN), false);
		this->mButtonScrollDown.setBackgroundImageFocus(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_H_BUTTON_DOWN_OVER), false);
		this->mButtonScrollDown.setBackgroundImageOver(this->mScrollBarSprite->getSpritePtr(IC_SCROLLBAR_H_BUTTON_DOWN_FOCUS), false);

		this->mTrackTop = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_TACK_UP);
		this->mTrackMid = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_TACK_MID);
		this->mTrackBottom = this->mScrollBarSprite->getSprite(IC_SCROLLBAR_H_TACK_DOWN);
	}
}

void Scrollbar::updateSpritePosition()
{
	if(this->mOrientation == ScrollBarOrientation::Vertical)
	{
		this->mTrackTop.setPosition(this->getX(), this->getY());
		this->mTrackBottom.setPosition(this->getX(), this->getY() + this->getHeight() - SPRITE_SIZE);
	}
	else
	{
		this->mTrackTop.setPosition(this->getX(), this->getY());
		this->mTrackBottom.setPosition(this->getX() + this->getWidth() - SPRITE_SIZE, this->getY());
	}
}






