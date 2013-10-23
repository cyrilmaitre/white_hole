#include "Movable.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Movable::Movable()
{
	for(int i = 0 ; i < MovableCardinality::Count; i++)
	{
		this->mVelocity[i] = 0;
		this->mQuickeningActive[i] = false;
	}

	this->mMoveX = 0;
	this->mMoveY = 0;
	this->mMode = MovableMode::ModeAdvanced;
}

Movable::~Movable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
float Movable::getVelocityAt( MovableCardinality cardinality )
{
	return this->mVelocity[cardinality];
}

void Movable::setVelocityAt( MovableCardinality cardinality, float p_velocity )
{
	if(p_velocity < 0)
		p_velocity = 0;
	else if(p_velocity > this->getVelocityMax())
		p_velocity = this->getVelocityMax();
	
	this->mVelocity[cardinality] = p_velocity;
}

bool Movable::isQuickeningActive()
{
	return	this->isQuickeningActiveAt(Movable::MovableCardinality::NorthEast) ||
			this->isQuickeningActiveAt(Movable::MovableCardinality::North) ||
			this->isQuickeningActiveAt(Movable::MovableCardinality::NorthWest) ||
			this->isQuickeningActiveAt(Movable::MovableCardinality::SouthEast) ||
			this->isQuickeningActiveAt(Movable::MovableCardinality::South) ||
			this->isQuickeningActiveAt(Movable::MovableCardinality::SouthWest) ||
			this->isQuickeningActiveAt(Movable::MovableCardinality::Normal);
}

bool Movable::isQuickeningActiveAt( MovableCardinality p_cardinality )
{
	return this->mQuickeningActive[p_cardinality];
}

void Movable::setQuickeningActiveAt( MovableCardinality p_cardinality, bool p_value )
{
	this;mQuickeningActive[p_cardinality] = p_value;
}

float Movable::getMoveX()
{
	return this->mMoveX;
}

float Movable::getMoveY()
{
	return this->mMoveY;
}

bool Movable::isMoving()
{
	if(this->getMode() == MovableMode::ModeAdvanced)
	{
		return	this->getVelocityAt(MovableCardinality::North) != 0 ||
				this->getVelocityAt(MovableCardinality::NorthEast) != 0 ||
				this->getVelocityAt(MovableCardinality::East) != 0 ||
				this->getVelocityAt(MovableCardinality::SouthEast) != 0 ||
				this->getVelocityAt(MovableCardinality::South) != 0 ||
				this->getVelocityAt(MovableCardinality::SouthWest) != 0 ||
				this->getVelocityAt(MovableCardinality::West) != 0 ||
				this->getVelocityAt(MovableCardinality::NorthWest) != 0;
	}
	else
	{
		return this->getVelocityAt(MovableCardinality::Normal) != 0;
	}
}

Movable::MovableMode Movable::getMode()
{
	return this->mMode;
}

void Movable::setMode( MovableMode p_mode )
{
	this->mMode = p_mode;
}


//*************************************************************
// Methode
//*************************************************************
void Movable::update()
{
	if(this->getMode() == MovableMode::ModeAdvanced)
	{
		for(int i = 0; i < MovableCardinality::Count; i++)
		{
			this->updateVelocityAt((MovableCardinality)i, this->mQuickeningActive[i], this->mQuickeningClock.getElapsedTimeAsMilliseconds());
		}
	}
	else
	{
		this->updateVelocityAt(MovableCardinality::Normal, this->mQuickeningActive[MovableCardinality::Normal], this->mQuickeningClock.getElapsedTimeAsMilliseconds());
	}
	this->updateMove();

	this->resetQuickeningClock();
	this->resetVelocityClock();
}

void Movable::updateMove()
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

		this->mMoveX = (TOOLS_COS45 * moveNE) + moveE + (TOOLS_COS45 * moveSE) - (TOOLS_COS45 * moveSO) - moveO - (TOOLS_COS45 * moveNO);
		this->mMoveY = (TOOLS_COS45 * moveSO) + moveS + (TOOLS_COS45 * moveSE) - (TOOLS_COS45 * moveNO) - moveN - (TOOLS_COS45 * moveNE);
	}
}

void Movable::updateVelocityAt( MovableCardinality p_cardinality, bool p_inc, long p_elapsedTimeAsMillisecond )
{
	float speedDeviation = ((float)p_elapsedTimeAsMillisecond * this->getQuickening()) / 1000.f;

	if(p_inc)
		this->setVelocityAt(p_cardinality, this->getVelocityAt(p_cardinality) + speedDeviation);
	else
		this->setVelocityAt(p_cardinality, this->getVelocityAt(p_cardinality) - speedDeviation);
}

void Movable::resetQuickeningActive()
{
	for(int i = 0 ; i < MovableCardinality::Count; i++)
	{
		this->mQuickeningActive[i] = false;
	}
}

void Movable::resetQuickeningClock()
{
	this->mQuickeningClock.restart();
}

void Movable::resetVelocityClock()
{
	this->mVelocityClock.restart();
}

float Movable::getDistanceBeforeDecelerate( MovableCardinality p_cardinality )
{
	return pow(this->getVelocityAt(p_cardinality), 2) / (this->getQuickening() * 2); 
}

float Movable::getDistanceXBeforeDecelerate( MovableCardinality p_cardinality )
{
	float distanceBeforeDecelerate = this->getDistanceBeforeDecelerate(p_cardinality);

	if(p_cardinality == MovableCardinality::East || p_cardinality == MovableCardinality::West)
		return distanceBeforeDecelerate;
	else if(p_cardinality == MovableCardinality::North || p_cardinality == MovableCardinality::South)
		return 0;
	else
		return Tools::getAbsolute(Tools::getCoordinate(45, distanceBeforeDecelerate).x);
}

float Movable::getDistanceYBeforeDecelerate( MovableCardinality p_cardinality )
{
	float distanceBeforeDecelerate = this->getDistanceBeforeDecelerate(p_cardinality);

	if(p_cardinality == MovableCardinality::North || p_cardinality == MovableCardinality::South)
		return distanceBeforeDecelerate;
	else if(p_cardinality == MovableCardinality::East || p_cardinality == MovableCardinality::West)
		return 0;
	else
		return Tools::getAbsolute(Tools::getCoordinate(45, distanceBeforeDecelerate).y);
}





