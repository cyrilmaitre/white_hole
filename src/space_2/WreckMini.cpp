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


//*************************************************************
// Constructor - Destructor
//*************************************************************
WreckMini::WreckMini( Wreck* p_parent, float p_velocityFactor )
{
	this->setObjectType(MapObjectType::TypeWreckMini);
	EntityManager::add(this);
	Game::game->getMap()->getMapObjectSelector()->addMapObject(this);

	this->setShieldMax(SHIELD);
	this->setArmorMax(ARMOR);
	this->setStructureMax(STRUCTURE);

	int velocityMin = VELOCITY_MIN * p_velocityFactor;
	int velocityMax = VELOCITY_MAX * p_velocityFactor;
	this->setVelocityMax(velocityMax);
	int vectorDirection = Tools::random(0, 7);
	if(vectorDirection == 0)	/// North
	{
		this->setVelocityAt(Movable::MovableCardinality::NorthWest, Tools::random(0, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::North, Tools::random(velocityMin, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::NorthEast, Tools::random(0, velocityMax));
	}
	else if(vectorDirection == 1)	// North-East
	{
		this->setVelocityAt(Movable::MovableCardinality::North, Tools::random(0, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::NorthEast, Tools::random(velocityMin, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::East, Tools::random(0, velocityMax));
	}
	else if(vectorDirection == 2)	// East
	{
		this->setVelocityAt(Movable::MovableCardinality::NorthEast, Tools::random(0, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::East, Tools::random(velocityMin, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::SouthEast, Tools::random(0, velocityMax));
	}
	else if(vectorDirection == 3)	// South-East
	{
		this->setVelocityAt(Movable::MovableCardinality::East, Tools::random(0, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::SouthEast, Tools::random(velocityMin, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::South, Tools::random(0, velocityMax));
	}
	else if(vectorDirection == 4)	// South
	{
		this->setVelocityAt(Movable::MovableCardinality::SouthEast, Tools::random(0, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::South, Tools::random(velocityMin, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::SouthWest, Tools::random(0, velocityMax));
	}
	else if(vectorDirection == 5)	// South-West
	{
		this->setVelocityAt(Movable::MovableCardinality::South, Tools::random(0, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::SouthWest, Tools::random(velocityMin, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::West, Tools::random(0, velocityMax));
	}
	else if(vectorDirection == 6)	// West
	{
		this->setVelocityAt(Movable::MovableCardinality::SouthWest, Tools::random(0, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::West, Tools::random(velocityMin, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::NorthWest, Tools::random(0, velocityMax));
	}
	else	// North-West
	{
		this->setVelocityAt(Movable::MovableCardinality::West, Tools::random(0, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::NorthWest, Tools::random(velocityMin, velocityMax));
		this->setVelocityAt(Movable::MovableCardinality::North, Tools::random(0, velocityMax));
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
}


//*************************************************************
// Methods
//*************************************************************
void WreckMini::update()
{
	EntityMovable::update();
}

void WreckMini::update( sf::Event p_event )
{
	EntityMovable::update(p_event);
}

void WreckMini::loadSprite()
{
	EntityMovable::loadSprite();

	if(this->mObjectSprite == NULL)
	{
		this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(SPRITE_BASE_PRE + Tools::buildStringWithInt(this->mSpriteId) + SPRITE_BASE_SUF));
		ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	}

	this->updateSprite();
}

void WreckMini::draw()
{
	EntityMovable::draw();
}
