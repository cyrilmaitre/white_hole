#include "Reactor.h"
#include "ToolsImage.h"
#include "EntityMovable.h"


//*************************************************************
// Define
//*************************************************************
#define JSON_OFFSETX				"x"
#define JSON_OFFSETY				"y"
#define JSON_TYPE					"type"
#define JSON_SIZE					"size"
#define JSON_REACTORALPHASPEED		"reactoralphaspeed"
#define REACTOR_SPRITE				"reactor_wisp.png"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Reactor::Reactor( EntityMovable* p_entity, Json::Value p_reactorJson )
{
	this->mEntityMovable = NULL;
	this->mReactor = NULL;
	this->mActive = false;
	this->mReactorAlpha = 0;
	this->mReactorAlphaSpeed = p_reactorJson.get(JSON_REACTORALPHASPEED, 0).asFloat();

	this->setEntityMovable(p_entity);
	this->setOffsetX(p_reactorJson.get(JSON_OFFSETX, 0).asInt());
	this->setOffsetY(p_reactorJson.get(JSON_OFFSETY, 0).asInt());
	this->setType((ReactorType)p_reactorJson.get(JSON_TYPE, 0).asInt());
	this->setSize(p_reactorJson.get(JSON_SIZE, 0).asInt());

	if(this->getSize() > 0)
	{
		this->mReactor = new sf::Sprite(*Resource::resource->getTexture(REACTOR_SPRITE));
		ToolsImage::setSpriteOriginCenter(this->mReactor);
		ToolsImage::resizeSprite(this->mReactor, this->getSize(), this->getSize());
	}
}

Reactor::~Reactor(void)
{
	if(this->mReactor != NULL)
		delete this->mReactor;
}


//*************************************************************
// Getters - Setters
//*************************************************************
EntityMovable* Reactor::getEntityMovable()
{
	return this->mEntityMovable;
}

void Reactor::setEntityMovable( EntityMovable* p_entity )
{
	this->mEntityMovable = p_entity;
}

Reactor::ReactorType Reactor::getType()
{
	return this->mType;
}

void Reactor::setType( ReactorType p_type )
{
	this->mType = p_type;
}

float Reactor::getOffsetX()
{
	return this->mOffsetX;
}

void Reactor::setOffsetX( float p_x )
{
	this->mOffsetX = p_x;
}

float Reactor::getOffsetY()
{
	return this->mOffsetY;
}

void Reactor::setOffsetY( float p_y )
{
	this->mOffsetY = p_y;
}

int Reactor::getSize()
{
	return this->mSize;
}

void Reactor::setSize( int p_size )
{
	this->mSize = p_size;
}

bool Reactor::isActive()
{
	return this->mActive;
}

void Reactor::setActve( bool p_active )
{
	this->mActive = p_active;
}


//*************************************************************
// Methods
//*************************************************************
void Reactor::update()
{
	if(this->getEntityMovable()->isVisible())
	{
		this->updateActive();
		this->updateReactorAlpha();
		this->updatePosition();
	}
}

void Reactor::updatePosition()
{
	if(this->mReactor != NULL)
	{
		sf::Vector2f reactorOffset;
		reactorOffset.x = this->getOffsetX();
		reactorOffset.y = this->getOffsetY();
		reactorOffset = Tools::rotatePoint(reactorOffset, this->getEntityMovable()->getRotation());
		this->mReactor->setPosition(this->getEntityMovable()->getScreenX() + reactorOffset.x, this->getEntityMovable()->getScreenY() + this->getEntityMovable()->getRocking() + reactorOffset.y);
		this->mReactor->setRotation(this->getEntityMovable()->getRotation());
	}
}

void Reactor::updateActive()
{
	if(	this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::NorthEast) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::North) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::NorthWest) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::SouthEast) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::South) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::SouthWest))
		this->mActive = true;
	else if(this->getType() == ReactorType::Right)
		this->mActive =	this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::West);
	else
		this->mActive =	this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::East);
}

void Reactor::updateReactorAlpha()
{
	if(this->isActive())
		this->mReactorAlpha += this->mReactorClock.getElapsedTimeAsSeconds() * this->mReactorAlphaSpeed;
	else
		this->mReactorAlpha -= this->mReactorClock.getElapsedTimeAsSeconds() * this->mReactorAlphaSpeed;
	this->mReactorClock.restart();
	if(this->mReactorAlpha < 0)
		this->mReactorAlpha = 0;
	else if(this->mReactorAlpha > 255)
		this->mReactorAlpha = 255;

	this->mReactor->setColor(sf::Color(255, 255, 255, this->mReactorAlpha));
}

void Reactor::draw()
{
	if(this->getEntityMovable()->isVisible())
	{
		if(this->mReactor != NULL)
			Resource::resource->getApp()->draw(*this->mReactor);
	}
}
