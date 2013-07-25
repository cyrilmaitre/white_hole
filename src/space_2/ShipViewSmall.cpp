#include "ShipViewSmall.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define DEFAULT_WIDTH			128
#define DEFAULT_HEIGHT			128
#define BACKGROUND_COLOR		sf::Color(128, 128, 128, 75)
#define BORDER_COLOR			sf::Color(128, 128, 128, 125)
#define BORDER_SIZE				2
#define ROTATION_SPEED			25	// degree per sec


//*************************************************************
// Constructor - Destructor
//*************************************************************
ShipViewSmall::ShipViewSmall(void)
{
	this->mSprite = NULL;
	this->mRotation = 0;

	this->setWidth(DEFAULT_WIDTH);
	this->setHeight(DEFAULT_HEIGHT);

	this->setBackgroundColor(BACKGROUND_COLOR, true);
	this->setBorderColor(BORDER_COLOR, true);
	this->setBorderSize(BORDER_SIZE, true);
}

ShipViewSmall::~ShipViewSmall(void)
{
	if(this->mSprite != NULL)
	{
		delete this->mSprite;
		this->mSprite = NULL;
	}
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool ShipViewSmall::hasShip()
{
	return this->mShip != NULL;
}

Ship* ShipViewSmall::getShip()
{
	return this->mShip;
}

void ShipViewSmall::setShip( Ship* p_ship )
{
	this->mShip = p_ship;
	this->notifyShipChanged();
}


//*************************************************************
// Methods
//*************************************************************
void ShipViewSmall::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->updateSpritePosition();
}

void ShipViewSmall::notifyShipChanged()
{
	if(this->hasShip())
	{
		if(this->mSprite != NULL)
		{
			delete this->mSprite;
			this->mSprite = NULL;
		}

		this->mSprite = new sf::Sprite(*Resource::resource->getTexture(this->getShip()->getShipModel()->getSprite()));
		ToolsImage::setSpriteOriginCenter(this->mSprite);
		this->mSprite->setRotation(this->mRotation);
		this->updateSpriteSize();
		this->updateSpritePosition();
	}
}

void ShipViewSmall::notifySizeChanged()
{
	Block::notifySizeChanged();
	this->updateSpriteSize();
}

void ShipViewSmall::update()
{
	this->updateRotation();
}

void ShipViewSmall::updateRotation()
{
	if(this->mSprite != NULL)
	{
		this->mRotation += this->mClock.getElapsedTimeAsSeconds() * ROTATION_SPEED;
		this->mClock.restart();
		if(this->mRotation > 360)
			this->mRotation = 0;
		this->mSprite->setRotation(this->mRotation);
	}
}

void ShipViewSmall::draw()
{
	Block::draw();
	if(this->mSprite != NULL)
		Resource::resource->getApp()->draw(*this->mSprite);
}

void ShipViewSmall::updateSpritePosition()
{
	if(this->mSprite != NULL)
		this->mSprite->setPosition(	this->getX() + ((this->getWidth() - this->mSprite->getLocalBounds().width) / 2) + this->mSprite->getLocalBounds().width / 2, 
									this->getY() + ((this->getHeight() - this->mSprite->getLocalBounds().height) / 2) + this->mSprite->getLocalBounds().height / 2);
}

void ShipViewSmall::updateSpriteSize()
{
	if(this->mSprite != NULL)
	{
		if(this->mSprite->getLocalBounds().width > this->getWidth() || this->mSprite->getLocalBounds().height > this->getHeight())
		{
			int size = this->getWidth() > this->getHeight() ? this->getWidth() : this->getHeight();
			this->mSprite->setScale((float)size / this->mSprite->getLocalBounds().width, (float)size / this->mSprite->getLocalBounds().height);
		}
	}
}

