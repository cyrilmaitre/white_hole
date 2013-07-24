#include "ImageGIF.h"

//******************************
// Constructeur - Destructeur 
//******************************
ImageGIF::ImageGIF( int p_nbFrame, int p_offsetX, int p_offsetY, float p_frequency, GIFOrientation p_orientation, sf::Texture* p_texture ): mSpriteParameter(NULL)
{
	this->mCurrentFrame				= 0;
	this->mSpriteParameter			= NULL;
	this->mSpriteParameterDelete	= false;
	this->mFirstFrame				= true;
	this->mFrameCount				= p_nbFrame;
	this->mOrientation				= p_orientation;
	this->mOffsetX					= p_offsetX;
	this->mOffsetY					= p_offsetY;
	this->mFrequency				= p_frequency;
	this->mSprite.setTexture(*p_texture);

	this->update();
	this->notifyPositionChanged();
}

ImageGIF::ImageGIF( SpriteParameter* p_sprite, float p_frequency, bool p_spriteDelete ): mSpriteParameter(NULL)
{
	this->mCurrentFrame				= 0;
	this->mSpriteParameter			= p_sprite;
	this->mSpriteParameterDelete	= p_spriteDelete;
	this->mFirstFrame				= true;
	this->mFrameCount				= this->mSpriteParameter->getSpriteColumns();
	this->mFrequency				= p_frequency;
	this->mLoop						= 0;

	this->update();
	this->notifyPositionChanged();
}

ImageGIF::~ImageGIF(void)
{
	if(this->mSpriteParameterDelete && this->mSpriteParameter != NULL)
		delete this->mSpriteParameter;
}


//******************************
// Getters - Setter
//******************************
long ImageGIF::getDurationInMilliseconds()
{
	return this->getDurationInSeconds() * 1000;
}

float ImageGIF::getDurationInSeconds()
{
	return this->mFrameCount * this->mFrequency;
}

sf::Sprite& ImageGIF::getSprite()
{
	if(this->mSpriteParameter != NULL)
		return this->mSpriteParameter->getSprite();
	else
		return this->mSprite;
}

int ImageGIF::getWidth()
{
	if(this->mSpriteParameter != NULL)
		return this->mSpriteParameter->getSpriteWidth();
	else
		return this->mSprite.getLocalBounds().width / this->mFrameCount;
}

int ImageGIF::getHeight()
{
	if(this->mSpriteParameter != NULL)
		return this->mSpriteParameter->getSpriteHeight();
	else
		return this->mSprite.getLocalBounds().height;
}

int ImageGIF::getLoop()
{
	return this->mLoop;
}


//******************************
// Méthodes
//******************************
void ImageGIF::update()
{
	if(this->isVisible())
	{
		if(this->mClockFrequency.getElapsedTimeAsSeconds() > this->mFrequency || this->mFirstFrame)
		{
			// Set firstFrame = false
			this->mFirstFrame = false;

			// Inc current frame
			this->mCurrentFrame++;

			if(this->mCurrentFrame >= this->mFrameCount)
			{
				this->mCurrentFrame = 0;
				this->mLoop++;
			}

			if(this->mSpriteParameter != NULL)
			{
				this->mSpriteParameter->selectSprite(this->mCurrentFrame, 0);
			}
			else
			{
				if(this->mOrientation == GIFOrientation::Horizontal)
					this->mSprite.setTextureRect(sf::IntRect(this->mOffsetX * this->mCurrentFrame, 0, this->mOffsetX, this->mOffsetY));			
				else
					this->mSprite.setTextureRect(sf::IntRect(0, this->mOffsetY * this->mCurrentFrame, this->mOffsetX, this->mOffsetY));		
			}

			this->mClockFrequency.restart();
		}	
	}
}

void ImageGIF::draw()
{
	if(this->isVisible())
	{
		if(this->mSpriteParameter != NULL)
			Resource::resource->getApp()->draw(this->mSpriteParameter->getSprite());
		else
			Resource::resource->getApp()->draw(this->mSprite);
	}
}

void ImageGIF::notifyPositionChanged()
{
	Object::notifyPositionChanged();
	if(this->mSpriteParameter != NULL)
		this->mSpriteParameter->getSprite().setPosition((float)this->getX(), (float)this->getY());
	else
		this->mSprite.setPosition((float)this->getX(), (float)this->getY());
}


