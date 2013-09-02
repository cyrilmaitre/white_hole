#include "WreckMini.h"
#include "ToolsImage.h"
#include "Wreck.h"
#include "Tools.h"
#include "EntityManager.h"
#include "Game.h"

//*************************************************************
// Define
//*************************************************************
#define SPRITE_BASE_PRE				"debris_"
#define SPRITE_BASE_SUF				".png"
#define SPRITE_EMBER_PRE			"debris_"
#define SPRITE_EMBER_SUF			"_ember.png"
#define SPRITE_COUNT				6
#define QUICKENING_MIN				75
#define QUICKENING_MAX				125
#define VELOCITY_MIN				100
#define VELOCITY_MAX				200
#define SIZE						32
#define ROTATION_VELOCITY_MIN		5
#define ROTATION_VELOCITY_MAX		10
#define SHIELD						0
#define ARMOR						0
#define STRUCTURE					100
#define EMBER_ALPHA_MIN				100
#define EMBER_ALPHA_MAX				255
#define EMBER_ALPHA_PROC_MIN		0.f		// sec
#define EMBER_ALPHA_PROC_MAX		4.f		// sec
#define EMBER_ALPHA_SPEED			60		// alpha per sec


//*************************************************************
// Constructor - Destructor
//*************************************************************
WreckMini::WreckMini( Wreck* p_parent )
{
	this->mEmberSprite = NULL;

	this->setObjectType(MapObjectType::TypeWreckMini);
	EntityManager::add(this);
	Game::game->getMap()->getMapObjectSelector()->addMapObject(this);

	this->setShieldMax(SHIELD);
	this->setArmorMax(ARMOR);
	this->setStructureMax(STRUCTURE);

	this->setVelocityMax(VELOCITY_MAX);
	int vectorDirection = Tools::random(0, 7);
	if(vectorDirection == 0)	/// North
	{
		this->setVelocityAt(Movable::MovableCardinality::NorthWest, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::North, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::NorthEast, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
	}
	else if(vectorDirection == 1)	// North-East
	{
		this->setVelocityAt(Movable::MovableCardinality::North, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::NorthEast, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::East, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
	}
	else if(vectorDirection == 2)	// East
	{
		this->setVelocityAt(Movable::MovableCardinality::NorthEast, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::East, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::SouthEast, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
	}
	else if(vectorDirection == 3)	// South-East
	{
		this->setVelocityAt(Movable::MovableCardinality::East, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::SouthEast, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::South, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
	}
	else if(vectorDirection == 4)	// South
	{
		this->setVelocityAt(Movable::MovableCardinality::SouthEast, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::South, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::SouthWest, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
	}
	else if(vectorDirection == 5)	// South-West
	{
		this->setVelocityAt(Movable::MovableCardinality::South, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::SouthWest, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::West, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
	}
	else if(vectorDirection == 6)	// West
	{
		this->setVelocityAt(Movable::MovableCardinality::SouthWest, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::West, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::NorthWest, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
	}
	else	// North-West
	{
		this->setVelocityAt(Movable::MovableCardinality::West, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::NorthWest, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
		this->setVelocityAt(Movable::MovableCardinality::North, Tools::random(VELOCITY_MIN, VELOCITY_MAX));
	}

	this->setRockingActived(false);
	this->setQuickening(Tools::random(QUICKENING_MIN, QUICKENING_MAX));
	this->setSize(SIZE, SIZE);
	this->setPosition(p_parent->Object::getX(), p_parent->Object::getY());
	this->setRotationInfinite(true);
	this->setRotationInfiniteRight(Tools::randomBool());
	this->setRotationVelocity(Tools::random(ROTATION_VELOCITY_MIN, ROTATION_VELOCITY_MAX));

	this->mSpriteId = Tools::random(1, SPRITE_COUNT);
}

WreckMini::~WreckMini(void)
{
	if(this->mEmberSprite != NULL)
		delete this->mEmberSprite;
}


//*************************************************************
// Methods
//*************************************************************
void WreckMini::update()
{
	EntityMovable::update();
	this->updateEmber();
}

void WreckMini::update( sf::Event p_event )
{
	EntityMovable::update(p_event);
}

void WreckMini::updateSprite()
{
	EntityMovable::updateSprite();

	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mEmberSprite != NULL)
		this->mEmberSprite->setPosition(objectPositionScreen.x, objectPositionScreen.y + this->getRocking());
}

void WreckMini::updateEmber()
{
	if(this->mEmberAlphaState == EmberAlphaState::Stopped && this->mEmberAlphaTickClock.getElapsedTimeAsSeconds() > this->mEmberAlphaNextTick)
		this->mEmberAlphaState = EmberAlphaState::Down;

	if(this->mEmberAlphaState == EmberAlphaState::Up)
	{
		this->mEmberAlpha += this->mEmberAlphaClock.getElapsedTimeAsSeconds() * EMBER_ALPHA_SPEED;
		if(this->mEmberAlpha > EMBER_ALPHA_MAX)
		{
			this->mEmberAlpha = EMBER_ALPHA_MAX;
			this->mEmberAlphaState = EmberAlphaState::Stopped;
			this->mEmberAlphaTickClock.restart();
			this->computeEmberAlphaNextTick();
		}
	}
	else if(this->mEmberAlphaState == EmberAlphaState::Down)
	{
		this->mEmberAlpha -= this->mEmberAlphaClock.getElapsedTimeAsSeconds() * EMBER_ALPHA_SPEED;
		if(this->mEmberAlpha < EMBER_ALPHA_MIN)
		{
			this->mEmberAlpha = EMBER_ALPHA_MIN;
			this->mEmberAlphaState = EmberAlphaState::Up;
		}
	}

	if(this->mEmberSprite != NULL)
		this->mEmberSprite->setColor(sf::Color(255,255,255,this->mEmberAlpha));
	this->mEmberAlphaClock.restart();
}

void WreckMini::loadSprite()
{
	EntityMovable::loadSprite();

	if(this->mObjectSprite == NULL)
	{
		this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(SPRITE_BASE_PRE + Tools::buildStringWithInt(this->mSpriteId) + SPRITE_BASE_SUF));
		ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	}

	if(this->mEmberSprite == NULL)
	{
		this->mEmberSprite = new sf::Sprite(*Resource::resource->getTexture(SPRITE_EMBER_PRE + Tools::buildStringWithInt(this->mSpriteId) + SPRITE_EMBER_SUF));
		ToolsImage::setSpriteOriginCenter(this->mEmberSprite);
		
		this->computeEmberAlphaNextTick();
		this->mEmberAlpha = EMBER_ALPHA_MAX;
		this->mEmberAlphaState = EmberAlphaState::Stopped;
		this->mEmberSprite->setColor(sf::Color(255,255,255,this->mEmberAlpha));
	}
}

void WreckMini::unloadSprite()
{
	EntityMovable::unloadSprite();

	if(this->mEmberSprite != NULL)
	{
		delete this->mEmberSprite;
		this->mEmberSprite = NULL;
	}
}

void WreckMini::notifyRotationChanged()
{
	EntityMovable::notifyRotationChanged();
	
	if(this->mEmberSprite != NULL)
		this->mEmberSprite->setRotation(this->getRotation());
}

void WreckMini::draw()
{
	EntityMovable::draw();

	if(this->isVisible())
	{
		//if(this->mEmberSprite != NULL)
		//	Resource::resource->getApp()->draw(*this->mEmberSprite);
	}
}

void WreckMini::computeEmberAlphaNextTick()
{
	this->mEmberAlphaNextTick = Tools::random((float)EMBER_ALPHA_PROC_MIN, (float)EMBER_ALPHA_PROC_MAX);
}
