#include "EntityMovable.h"
#include "Camera.h"
#include "ToolsMap.h"
#include "EntityManager.h"
#include "CharacterShip.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define REACTOR_IMG		"reactor_wisp.png"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
EntityMovable::EntityMovable( double p_x, double p_y, int p_plane ) : Entity(p_plane)
{
	this->mTargetX = 0;
	this->mTargetY = 0;
	this->mTargetPositionDefined = false;
	this->mSourceX = p_x;
	this->mSourceY = p_y;
	this->mTargetGenRange = 0;

	this->setTargetDistanceMax(TARGET_DISTANCE_MAX_DEFAULT);
}

EntityMovable::~EntityMovable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int EntityMovable::getTargetDistanceMax()
{
	return this->mTargetDistanceMax;
}

void EntityMovable::setTargetDistanceMax( int p_max )
{
	if(p_max < 0)
		p_max = 0;

	this->mTargetDistanceMax = p_max;
}

double EntityMovable::getSourceX()
{
	return this->mSourceX;
}

void EntityMovable::setSourceX( double p_x )
{
	this->mSourceX = p_x;
}

double EntityMovable::getSourceY()
{
	return this->mSourceY;
}

void EntityMovable::setSourceY( double p_y )
{
	this->mSourceY = p_y;
}

double EntityMovable::getTargetX()
{
	return this->mTargetX;
}

double EntityMovable::getTargetY()
{
	return this->mTargetY;
}

void EntityMovable::setTargetPosition( double p_x, double p_y )
{
	this->mTargetX = p_x;
	this->mTargetY = p_y;
	this->setTargetPositionDefined(true);
}

bool EntityMovable::isTargetPositionDefined()
{
	return this->mTargetPositionDefined;
}

void EntityMovable::setTargetPositionDefined( bool p_value )
{
	this->mTargetPositionDefined = p_value;
}

double EntityMovable::getTargetGenRange()
{
	return this->mTargetGenRange;
}

void EntityMovable::setTargetGenRange( double p_range )
{
	this->mTargetGenRange = p_range;
}


//*************************************************************
// Methods
//*************************************************************
void EntityMovable::update()
{
	Entity::update();

	if(this->getTarget()->isEntityValid())
		this->setTargetPosition(this->getTarget()->getEntity()->getX(this->getPlane()), this->getTarget()->getEntity()->getY(this->getPlane()));	

	if(this->isTargetReached())
		this->setTargetPositionDefined(false);

	this->updateRotation();
	this->updateQuickeningActive();
	Movable::update();
	this->updatePosition();
}

void EntityMovable::updateRotation()
{
	if(this->isTargetPositionDefined())
	{
		this->setRotationTarget(Tools::getAngle(this->Object::getX(), this->Object::getY(), this->getTargetX(), this->getTargetY()));
	}
	else if(this->getTarget()->isEntityValid())
	{
		this->setRotationTarget(Tools::getAngle(this->Object::getX(), this->Object::getY(), this->getTarget()->getEntity()->getX(this->getPlane()), this->getTarget()->getEntity()->getY(this->getPlane())));
	}
}

void EntityMovable::updatePosition()
{
	this->setX(this->Object::getX() + this->getMoveX());
	this->setY(this->Object::getY() + this->getMoveY());
}

void EntityMovable::updateRocking()
{
	if(!this->isMoving())
		Rockable::updateRocking();
}

void EntityMovable::updateSprite()
{
	Entity::updateSprite();
}

void EntityMovable::update( sf::Event p_event )
{
	Entity::update(p_event);
}

void EntityMovable::draw()
{
	Entity::draw();
}

void EntityMovable::updateQuickeningActive()
{
	if(this->getMode() == MovableMode::ModeAdvanced)
	{
		if(this->isTargetPositionDefined())
		{
			float distance = ToolsMap::getDistance(this, this->getTargetX(), this->getTargetY());
			if(distance > this->getTargetDistanceMax())
				this->setQuickeningActiveAt(MovableCardinality::North, true);
			else
				this->setQuickeningActiveAt(MovableCardinality::North, false);
		}
		else
		{
			this->setQuickeningActiveAt(MovableCardinality::North, false);
		}
	}
	else if(this->getMode() == MovableMode::ModeNormal)
	{
		if(this->isTargetPositionDefined())
		{
			float distance = ToolsMap::getDistance(this, this->getTargetX(), this->getTargetY());
			if(distance > this->getTargetDistanceMax())
				this->setQuickeningActiveAt(MovableCardinality::Normal, distance > this->getDistanceBeforeDecelerate(MovableCardinality::Normal));
			else
				this->setQuickeningActiveAt(MovableCardinality::Normal, false);
		}
		else
		{
			this->setQuickeningActiveAt(MovableCardinality::Normal, false);
		}
	}
	else
	{
		if(this->isTargetPositionDefined())
			this->setQuickeningActiveAt(MovableCardinality::Normal, true);
		else
			this->setQuickeningActiveAt(MovableCardinality::Normal, false);
	}
}

void EntityMovable::updateMove()
{
	if(this->getMode() == MovableMode::ModeAdvanced)
	{
		float factor = (float)this->mVelocityClock.getElapsedTimeAsMilliseconds() / 1000.f;
		float moveN = this->getVelocityAt(MovableCardinality::North) * factor;
		float moveNE = this->getVelocityAt(MovableCardinality::NorthEast) * factor;
		float moveE = this->getVelocityAt(MovableCardinality::East) * factor;
		float moveSE = this->getVelocityAt(MovableCardinality::SouthEast) * factor;
		float moveS = this->getVelocityAt(MovableCardinality::South) * factor;
		float moveSO = this->getVelocityAt(MovableCardinality::SouthWest) * factor;
		float moveO = this->getVelocityAt(MovableCardinality::West) * factor;
		float moveNO = this->getVelocityAt(MovableCardinality::NorthWest) * factor;

		float tmpMoveX = (TOOLS_COS45 * moveNE) + moveE + (TOOLS_COS45 * moveSE) - (TOOLS_COS45 * moveSO) - moveO - (TOOLS_COS45 * moveNO);
		float tmpMoveY = (TOOLS_COS45 * moveSO) + moveS + (TOOLS_COS45 * moveSE) - (TOOLS_COS45 * moveNO) - moveN - (TOOLS_COS45 * moveNE);
		float angle = this->getRotation();
		float angleRadian = Tools::degreeToRadian(angle);

		this->mMoveX = cos(angleRadian) * (tmpMoveX) - sin(angleRadian) * (tmpMoveY);
		this->mMoveY = sin(angleRadian) * (tmpMoveX) + cos(angleRadian) * (tmpMoveY);
	}
	else
	{
		if(this->isTargetPositionDefined())
		{
			float move = this->getVelocityAt(MovableCardinality::Normal) * ((float)this->mVelocityClock.getElapsedTimeAsMilliseconds() / 1000.f);
			float angle = Tools::getAngle(this->Object::getX(), this->Object::getY(), this->getTargetX(), this->getTargetY());

			sf::Vector2f tmpVector = Tools::getCoordinate(angle, move);
			this->mMoveX = tmpVector.x;
			this->mMoveY = tmpVector.y;
		}
	}
}

bool EntityMovable::isTargetReached()
{
	if(this->isTargetPositionDefined())
		return ToolsMap::getDistance(this, this->getTargetX(), this->getTargetY()) <= this->getTargetDistanceMax();
	else
		return true;
}

double EntityMovable::generateTargetPositionX()
{
	bool positive = Tools::random(0, 1) == 0;
	double distance = Tools::randomZeroToOne() * this->getTargetGenRange();

	if(positive)
		return this->getSourceX() + distance;
	else
		return this->getSourceX() - distance;
}

double EntityMovable::generateTargetPositionY()
{
	bool positive = Tools::random(0, 1) == 0;
	double distance = Tools::randomZeroToOne() * this->getTargetGenRange();

	if(positive)
		return this->getSourceY() + distance;
	else
		return this->getSourceY() - distance;
}

void EntityMovable::loadSprite()
{
	Entity::loadSprite();

	for(int i = 0; i < this->getReactorCount(); i++)
	{
		sf::Sprite* currentSprite = new sf::Sprite(*Resource::resource->getTexture(REACTOR_IMG));
		ToolsImage::setSpriteOriginCenter(currentSprite);
		ToolsImage::resizeSprite(currentSprite, this->getReactorSize(), this->getReactorSize());

	}
}

void EntityMovable::unloadSprite()
{
	Entity::unloadSprite();

	for(int i = 0; i < this->mReactorSprite.size(); i++)
	{
		if(this->mReactorSprite[i] != NULL)
			delete this->mReactorSprite[i];
	}
	this->mReactorSprite.clear();
}





