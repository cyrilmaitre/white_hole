#include "Animation.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Animation::Animation( sf::Texture* p_texture, long p_spriteDuration, int p_x, int p_y )
{
	this->init();
	this->mSprite.setTexture(*p_texture);
	this->mSpriteDuration = p_spriteDuration;

	this->setAnimationX(p_x);
	this->setAnimationY(p_y);	
}

Animation::Animation( sf::Sprite p_sprite, long p_spriteDuration, int p_x , int p_y )
{
	this->init();
	this->mSprite = p_sprite;
	this->mSpriteDuration = p_spriteDuration;

	this->setAnimationX(p_x);
	this->setAnimationY(p_y);
}

Animation::Animation( ImageGIF* p_spriteGif, int p_spriteGifLoop, int p_x , int p_y )
{
	this->init();
	this->mSpriteGif = p_spriteGif;
	this->mSpriteGifLoop = p_spriteGifLoop;

	this->setAnimationX(p_x);
	this->setAnimationY(p_y);
}

Animation::~Animation(void)
{
	if(this->mSpriteGif != NULL)
		delete this->mSpriteGif;
}

void Animation::init()
{
	this->mSpriteDuration = 0;
	this->mSpriteGif = NULL;
	this->mSpriteGifLoop = 0;

	this->mRotationDuration = -1;
	this->mRotationAngleStart = 0;
	this->mRotationAngleEnd = 0;

	this->mScaleDuration = -1;
	this->mScaleXStart = 0;
	this->mScaleYStart = 0;
	this->mScaleXEnd = 0;
	this->mScaleYEnd = 0;
	
	this->mTranslationDuration = -1;
	this->mTranslationXStart = 0;
	this->mTranslationYStart = 0;
	this->mTranslationXEnd = 0;
	this->mTranslationYEnd = 0;

	this->mRelatedObjectMap = NULL;
	this->mRelatedObject = NULL;

	this->mRelatedObjectOffsetX = 0;
	this->mRelatedObjectOffsetY = 0;

	this->mStarted = false;
	this->mStoped = false;
}


//*************************************************************
// Getters - Setter
//*************************************************************
int Animation::getAnimationX()
{
	if(this->mSpriteGif != NULL)
		return this->mSpriteGif->getX();
	else
		return this->mSprite.getPosition().x;
}

int Animation::getAnimationY()
{
	if(this->mSpriteGif != NULL)
		return this->mSpriteGif->getY();
	else
		return this->mSprite.getPosition().y;
}

void Animation::setAnimationX( int p_x )
{
	if(this->mSpriteGif != NULL)
		this->mSpriteGif->setX(p_x);
	else
		this->mSprite.setPosition(p_x, this->getAnimationY());
}

void Animation::setAnimationY( int p_y )
{
	if(this->mSpriteGif != NULL)
		this->mSpriteGif->setY(p_y);
	else
		this->mSprite.setPosition(this->getAnimationX(), p_y);
}

long Animation::getAnimationDuration()
{
	if(this->mSpriteGif != NULL)
		return this->mSpriteGif->getDurationInMilliseconds() * this->mSpriteGifLoop;
	else
		return this->mSpriteDuration;
}

long Animation::getRotationDuration()
{
	return this->mRotationDuration;
}

long Animation::getScaleDuration()
{
	return this->mScaleDuration;
}

long Animation::getTranslationDuration()
{
	return this->mTranslationDuration;
}

Object* Animation::getRelatedObject()
{
	return this->mRelatedObject;
}

void Animation::setRelatedObject( Object* p_object )
{
	this->mRelatedObject = p_object;
}

MapObject* Animation::getRelatedObjectMap()
{
	return this->mRelatedObjectMap;
}

void Animation::setRelatedObjectMap( MapObject* p_objectMap )
{
	this->mRelatedObjectMap = p_objectMap;
}

bool Animation::isFinished()
{
	return	this->isSpriteFinished() ||
			this->isStoped() ||
		   (this->isRotationFinished() &&
			this->isScaleFinished() &&
			this->isTranslationFinished() &&
			(this->mRotationDuration >= 0 || this->mScaleDuration >= 0 || this->mTranslationDuration >=0));
}

bool Animation::isStarted()
{
	return this->mStarted;
}

bool Animation::isStoped()
{
	return this->mStoped;
}

int Animation::getRelatedObjectOffsetX()
{
	return this->mRelatedObjectOffsetX;
}

void Animation::setRelatedObjectOffsetX( int p_x )
{
	this->mRelatedObjectOffsetX = p_x;
}

int Animation::getRelatedObjectOffsetY()
{
	return this->mRelatedObjectOffsetY;
}

void Animation::setRelatedObjectOffsetY( int p_y )
{
	this->mRelatedObjectOffsetY = p_y;
}

bool Animation::canBeRotated()
{
	return this->isStarted() && this->mRotationDuration >= 0;
}

bool Animation::canBeScaled()
{
	return this->isStarted() && this->mScaleDuration >= 0;
}

bool Animation::canBeTranslated()
{
	return this->isStarted() && this->mTranslationDuration >= 0 && this->mRelatedObject == NULL && this->mRelatedObjectMap == NULL;
}

float Animation::getCurrentRotation()
{
	if(this->mClock.getElapsedTimeAsMilliseconds() > this->mRotationDuration)
		return this->mRotationAngleEnd;

	if(this->mRotationAngleDirection == ANIMATION_ROTATION_DIRECTION_RIGHT)
		return this->mRotationAngleStart + ((float)this->mClock.getElapsedTimeAsMilliseconds() / (float)this->mRotationDuration) * (this->mRotationAngleDiff);
	else
		return this->mRotationAngleStart - ((float)this->mClock.getElapsedTimeAsMilliseconds() / (float)this->mRotationDuration) * (this->mRotationAngleDiff);
}

float Animation::getCurrentScaleX()
{
	if(this->mClock.getElapsedTimeAsMilliseconds() > this->mScaleDuration)
		return this->mScaleXEnd;

	return this->mScaleXStart + ((float)this->mClock.getElapsedTimeAsMilliseconds() / (float)this->mScaleDuration) * this->mScaleXDiff;
}

float Animation::getCurrentScaleY()
{
	if(this->mClock.getElapsedTimeAsMilliseconds() > this->mScaleDuration)
		return this->mScaleYEnd;

	return this->mScaleYStart + ((float)this->mClock.getElapsedTimeAsMilliseconds() / (float)this->mScaleDuration) * this->mScaleYDiff;
}

int Animation::getCurrentTranslationX()
{
	if(this->mClock.getElapsedTimeAsMilliseconds() > this->mTranslationDuration)
		return this->mTranslationXEnd;

	return this->mTranslationXStart + ((float)this->mClock.getElapsedTimeAsMilliseconds() / (float)this->mTranslationDuration) * this->mTranslationXDiff; 
}

int Animation::getCurrentTranslationY()
{
	if(this->mClock.getElapsedTimeAsMilliseconds() > this->mTranslationDuration)
		return this->mTranslationYEnd;

	return this->mTranslationYStart + ((float)this->mClock.getElapsedTimeAsMilliseconds() / (float)this->mTranslationDuration) * this->mTranslationYDiff; 	
}

bool Animation::isRotationFinished()
{
	return this->isStarted() && this->mClock.getElapsedTimeAsMilliseconds() > this->mRotationDuration;
}

bool Animation::isScaleFinished()
{
	return this->isStarted() && this->mClock.getElapsedTimeAsMilliseconds() > this->mScaleDuration;
}

bool Animation::isTranslationFinished()
{
	return this->isStarted() && this->mClock.getElapsedTimeAsMilliseconds() > this->mTranslationDuration;
}

bool Animation::isSpriteFinished()
{
	if(this->mSpriteGif != NULL)
		return this->mSpriteGifLoop >= 0 && this->mSpriteGif->getLoop() > this->mSpriteGifLoop;
	else
		return this->mSpriteDuration >= 0 && this->mClock.getElapsedTimeAsMilliseconds() > this->mSpriteDuration;
}

sf::Sprite Animation::getCurrentSprite()
{
	if(this->mSpriteGif != NULL)
		return this->mSpriteGif->getSprite();
	else
		return this->mSprite;
}

void Animation::setSpriteOriginCenter()
{
	if(this->mSpriteGif != NULL)
		this->mSpriteGif->getSprite().setOrigin(this->mSpriteGif->getSprite().getLocalBounds().width / 2, this->mSpriteGif->getSprite().getLocalBounds().height / 2);
	else
		this->mSprite.setOrigin(this->mSprite.getLocalBounds().width / 2, this->mSprite.getLocalBounds().height / 2);
}


//*************************************************************
// Methods
//*************************************************************
void Animation::update()
{
	this->updateRelatedObject();
	this->updateRotation();
	this->updateScale();
	this->updateTranslation();

	if(this->mSpriteGif != NULL)
		this->mSpriteGif->update();
}

void Animation::updateRelatedObject()
{
	if(this->mRelatedObjectMap != NULL)
	{
		this->setAnimationX(this->mRelatedObjectMap->getScreenX() + this->getRelatedObjectOffsetX());
		this->setAnimationY(this->mRelatedObjectMap->getScreenY() + this->getRelatedObjectOffsetY());
	}
	else if(this->mRelatedObject != NULL)
	{
		this->setAnimationX(this->mRelatedObject->getX() + this->getRelatedObjectOffsetX());
		this->setAnimationY(this->mRelatedObject->getY() + this->getRelatedObjectOffsetY());
	}
}

void Animation::updateRotation()
{
	if(this->canBeRotated())
	{
		if(this->mSpriteGif != NULL)
			this->mSpriteGif->getSprite().setRotation(this->getCurrentRotation());
		else
			this->mSprite.setRotation(this->getCurrentRotation());
	}
}

void Animation::updateScale()
{
	if(this->canBeScaled())
	{
		if(this->mSpriteGif != NULL)
			this->mSpriteGif->getSprite().setScale(this->getCurrentScaleX(), this->getCurrentScaleY());
		else
			this->mSprite.setScale(this->getCurrentScaleX(), this->getCurrentScaleY());
	}
}

void Animation::updateTranslation()
{
	if(this->canBeTranslated())
	{
		if(this->mSpriteGif != NULL)
		{
			this->mSpriteGif->setX(this->getCurrentTranslationX());
			this->mSpriteGif->setY(this->getCurrentTranslationY());
		}
		else
		{
			this->mSprite.setPosition(this->getCurrentTranslationX(), this->getCurrentTranslationY());
		}
	}
}

void Animation::draw()
{
	if(this->isStarted())
	{
		if(this->mSpriteGif != NULL)
			this->mSpriteGif->draw();
		else
			Resource::resource->getApp()->draw(this->mSprite);
	}
}

void Animation::rotate( float p_angleStart, float p_angleEnd, long p_duration, bool p_rotationDirection )
{
	this->mRotationAngleStart = p_angleStart;
	this->mRotationAngleEnd = p_angleEnd;
	this->mRotationAngleDirection = p_rotationDirection;
	this->mRotationDuration = p_duration;

	float tmpDiff = 0;
	if(this->mRotationAngleDirection == ANIMATION_ROTATION_DIRECTION_RIGHT)
	{
		if(this->mRotationAngleEnd > this->mRotationAngleStart)
			tmpDiff = this->mRotationAngleEnd - this->mRotationAngleStart;
		else if(this->mRotationAngleEnd < this->mRotationAngleStart) 
			tmpDiff = 360 - this->mRotationAngleStart + this->mRotationAngleEnd;
		else
			tmpDiff = 360;
	}
	else
	{
		if(this->mRotationAngleEnd > this->mRotationAngleStart)
			tmpDiff = 360 - this->mRotationAngleEnd + this->mRotationAngleStart;
		else if(this->mRotationAngleEnd < this->mRotationAngleStart)
			tmpDiff = this->mRotationAngleStart - this->mRotationAngleEnd;
		else
			tmpDiff = 360;
	}

	this->mRotationAngleDiff = tmpDiff;
}

void Animation::rotate( float p_angleEnd, long p_duration, bool p_rotationDirection )
{
	this->rotate((this->mSpriteGif != NULL ? this->mSpriteGif->getSprite().getRotation() : this->mSprite.getRotation()), p_angleEnd, p_duration, p_rotationDirection);
}

void Animation::scale( float p_scaleXStart, float p_scaleYStart, float p_scaleXEnd, float p_scaleYEnd, long p_duration )
{	
	this->mScaleDuration = p_duration;
	this->mScaleXStart = p_scaleXStart;
	this->mScaleYStart = p_scaleYStart;
	this->mScaleXEnd = p_scaleXEnd;
	this->mScaleYEnd = p_scaleYEnd;

	this->mScaleXDiff = this->mScaleXEnd - this->mScaleXStart;
	this->mScaleYDiff = this->mScaleYEnd - this->mScaleYStart;
}

void Animation::scale( float p_scaleXEnd, float p_scaleYEnd, long p_duration )
{
	this->scale(this->mSpriteGif != NULL ? this->mSpriteGif->getSprite().getScale().x : this->mSprite.getScale().x,
				this->mSpriteGif != NULL ? this->mSpriteGif->getSprite().getScale().y : this->mSprite.getScale().y,
				p_scaleXEnd, p_scaleYEnd, p_duration);
}

void Animation::scaleNewSize( int p_newWidth, int p_newHeight, long p_duration )
{
	this->scale(this->mSpriteGif != NULL ? this->mSpriteGif->getSprite().getScale().x : this->mSprite.getScale().x,
				this->mSpriteGif != NULL ? this->mSpriteGif->getSprite().getScale().y : this->mSprite.getScale().y,
				this->mSpriteGif != NULL ? (float)p_newWidth / (float)this->mSpriteGif->getWidth() : (float)p_newWidth / (float)this->mSprite.getLocalBounds().width, 
				this->mSpriteGif != NULL ? (float)p_newHeight / (float)this->mSpriteGif->getHeight() : (float)p_newHeight / (float)this->mSprite.getLocalBounds().height, 
				p_duration);
}

void Animation::translate( int p_positionXStart, int p_positionYStart, int p_positionXEnd, int p_positionYEnd, long p_duration )
{
	this->mTranslationDuration = p_duration;
	this->mTranslationXStart = p_positionXStart;
	this->mTranslationYStart = p_positionYStart;
	this->mTranslationXEnd = p_positionXEnd;
	this->mTranslationYEnd = p_positionYEnd;

	this->mTranslationXDiff = this->mTranslationXEnd - this->mTranslationXStart;
	this->mTranslationYDiff = this->mTranslationYEnd - this->mTranslationYStart;
}

void Animation::translate( int p_positionXEnd, int p_positionYEnd, long p_duration )
{
	this->translate(this->mSpriteGif != NULL ? this->mSpriteGif->getX() : this->mSprite.getPosition().x,
					this->mSpriteGif != NULL ? this->mSpriteGif->getY() : this->mSprite.getPosition().y,
					p_positionXEnd, p_positionYEnd, p_duration);
}

void Animation::start()
{
	this->mStarted = true;
	this->mStoped = false;
	this->restart();
}

void Animation::restart()
{
	this->mClock.restart();
}

void Animation::stop()
{
	this->mStoped = true;
	this->mStarted = false;
}




