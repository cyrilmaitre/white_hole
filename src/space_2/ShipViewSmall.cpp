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
#define ROTATION_FREQ			500	// ms


//*************************************************************
// Constructor - Destructor
//*************************************************************
ShipViewSmall::ShipViewSmall(void)
{
	this->mSprite = NULL;
	this->mSpriteColumn = 0;

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

		this->mSpriteColumn = 0;
		this->mSprite = SpriteParameterFactory::getSpriteParameter(this->getShip()->getShipModel()->getSprite(), SHIP_SPRITE_COLUMN, SHIP_SPRITE_LINE, false);
		this->mSprite->selectSprite(this->mSpriteColumn, 0);
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
	if(this->mSprite != NULL)
	{
		if(this->mClock.getElapsedTimeAsMilliseconds() > ROTATION_FREQ)
		{
			this->mSpriteColumn++;
			if(this->mSpriteColumn >= SHIP_SPRITE_COLUMN)
				this->mSpriteColumn = 0;

			this->mSprite->selectSprite(this->mSpriteColumn, 0);
			this->mClock.restart();
		}
	}
}

void ShipViewSmall::draw()
{
	Block::draw();
	if(this->mSprite != NULL)
	{
		Resource::resource->getApp()->draw(this->mSprite->getSprite());
	}
}

void ShipViewSmall::updateSpritePosition()
{
	if(this->mSprite != NULL)
		this->mSprite->getSprite().setPosition(this->getX(), this->getY());
}

void ShipViewSmall::updateSpriteSize()
{
	if(this->mSprite != NULL)
	{
		if(this->mSprite->getSprite().getLocalBounds().width > this->getWidth() || this->mSprite->getSprite().getLocalBounds().height > this->getHeight())
		{
			int size = this->getWidth() > this->getHeight() ? this->getWidth() : this->getHeight();
			this->mSprite->getSprite().setScale((float)size / this->mSprite->getSpriteWidth(), (float)size / this->mSprite->getSpriteHeight());
		}
	}
}
