#include "ReactorEffect.h"
#include "ToolsImage.h"
#include "EntityMovable.h"
#include "AutoManager.h"
#include "ReactorDustEffect.h"


//*************************************************************
// Define
//*************************************************************
#define JSON_TYPE					"type"
#define JSON_REACTORALPHASPEED		"reactoralphaspeed"
#define REACTOR_SPRITE				"reactor_wisp.png"
#define REACTORDUST_TICK_MIN		50		// millisec
#define REACTORDUST_TICK_MAX		100		// millisec


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
ReactorEffect::ReactorEffect( EntityMovable* p_entity, Json::Value p_reactorJson ) : EntityMovableEffect(p_entity, p_reactorJson)
{
	this->mReactor = NULL;
	this->mActive = false;
	this->mReactorAlpha = 0;
	this->mReactorAlphaSpeed = p_reactorJson.get(JSON_REACTORALPHASPEED, 0).asFloat();

	this->setType((ReactorEffectType)p_reactorJson.get(JSON_TYPE, 0).asInt());
	this->computeReactorDustTick();

	this->mReactor = new sf::Sprite(*Resource::resource->getTexture(REACTOR_SPRITE));
	ToolsImage::setSpriteOriginCenter(this->mReactor);
	ToolsImage::resizeSprite(this->mReactor, this->getSize(), this->getSize());
}

ReactorEffect::ReactorEffect( EntityMovable* p_entity, float p_offsetX, float p_offsetY, int p_size, int p_type, float p_alphaReactorSpeed ) : EntityMovableEffect(p_entity, p_offsetX, p_offsetY, p_size)
{
	this->mReactor = NULL;
	this->mActive = false;
	this->mReactorAlpha = 0;
	this->mReactorAlphaSpeed = p_alphaReactorSpeed;

	this->setType((ReactorEffectType)p_type);
	this->computeReactorDustTick();

	this->mReactor = new sf::Sprite(*Resource::resource->getTexture(REACTOR_SPRITE));
	ToolsImage::setSpriteOriginCenter(this->mReactor);
	ToolsImage::resizeSprite(this->mReactor, this->getSize(), this->getSize());
}

ReactorEffect::~ReactorEffect(void)
{
	if(this->mReactor != NULL)
		delete this->mReactor;
}


//*************************************************************
// Getters - Setters
//*************************************************************
ReactorEffect::ReactorEffectType ReactorEffect::getType()
{
	return this->mType;
}

void ReactorEffect::setType( ReactorEffectType p_type )
{
	this->mType = p_type;
}

bool ReactorEffect::isActive()
{
	return this->mActive;
}

void ReactorEffect::setActve( bool p_active )
{
	this->mActive = p_active;
}


//*************************************************************
// Methods
//*************************************************************
void ReactorEffect::update()
{
	EntityMovableEffect::update();
	if(this->getEntityMovable()->isVisible())
	{
		this->updateActive();
		this->updateReactorAlpha();
		this->updatePosition();
		this->updateReactorDust();
	}
}

void ReactorEffect::updatePosition()
{
	if(this->mReactor != NULL)
	{
		this->mReactor->setPosition(this->getEntityMovable()->getScreenX() + this->getOffsetXRotate(), 
									this->getEntityMovable()->getScreenY() + this->getEntityMovable()->getRocking() + this->getOffsetYRotate());
	}
}

void ReactorEffect::updateActive()
{
	if(	this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::NorthEast) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::North) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::NorthWest) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::SouthEast) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::South) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::SouthWest) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::Normal))
		this->mActive = true;
	else if(this->getType() == ReactorEffectType::Right)
		this->mActive =	this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::West);
	else if(this->getType() == ReactorEffectType::Left)
		this->mActive =	this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::East);
	else if(this->getType() == ReactorEffectType::Single)
		this->mActive = this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::West) || this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::East);
}

void ReactorEffect::updateReactorAlpha()
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

void ReactorEffect::updateReactorDust()
{
	if(	this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::NorthEast) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::North) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::NorthWest) ||
		this->getEntityMovable()->isQuickeningActiveAt(Movable::MovableCardinality::Normal))
	{
		if(this->mReactorDustClock.getElapsedTimeAsMilliseconds() > this->mReactorDustTick)
		{
			double mDustX = this->getEntityMovable()->Object::getX() + this->getOffsetXRotate();
			double mDustY = this->getEntityMovable()->Object::getY() + this->getEntityMovable()->getRocking() + this->getOffsetYRotate();
			AutoManager::add(new ReactorDustEffect(mDustX, mDustY, this->getSize(), this->mReactorAlpha));
			this->computeReactorDustTick();
			this->mReactorDustClock.restart();
		}
	}
}

void ReactorEffect::draw()
{
	EntityMovableEffect::draw();
	if(this->getEntityMovable()->isVisible())
	{
		if(this->mReactor != NULL)
			Resource::resource->getApp()->draw(*this->mReactor);
	}
}

void ReactorEffect::computeReactorDustTick()
{
	this->mReactorDustTick = Tools::random(REACTORDUST_TICK_MIN, REACTORDUST_TICK_MAX);
}
