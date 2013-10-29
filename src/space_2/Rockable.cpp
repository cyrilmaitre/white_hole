#include "Rockable.h"


//*************************************************************
// Define
//*************************************************************
#define ROCKING_AMPLITUDE				5
#define ROCKING_SPEED					3	// per sec


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Rockable::Rockable(void)
{
	this->mRocking = 0;
	this->setRockingState(RockingState::ActiveUp);
}

Rockable::~Rockable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
float Rockable::getRocking()
{
	return this->mRocking;
}

void Rockable::setRocking( float p_rocking )
{
	if(p_rocking > ROCKING_AMPLITUDE)
	{
		this->setRockingState(RockingState::ActiveDown);
		this->mRocking = 2 * ROCKING_AMPLITUDE - p_rocking;
	}
	else if(p_rocking < -ROCKING_AMPLITUDE)
	{
		this->setRockingState(RockingState::ActiveUp);
		this->mRocking = -2 * ROCKING_AMPLITUDE - p_rocking;
	}
	else
	{
		this->mRocking = p_rocking;
	}
}

Rockable::RockingState Rockable::getRockingState()
{
	return this->mRockingState;
}

void Rockable::setRockingState( RockingState p_state )
{
	this->mRockingState = p_state;
}


//*************************************************************
// Methods
//*************************************************************
void Rockable::update()
{
	if(this->mRockingState != RockingState::Inactive)
		this->updateRocking();
}

void Rockable::updateRocking()
{
	float offsetRocking = this->mRockingClock.getElapsedTimeAsSeconds() * ROCKING_SPEED;
	this->mRockingClock.restart();

	if(this->mRockingState == RockingState::ActiveUp)
		this->setRocking(this->mRocking + offsetRocking);
	else
		this->setRocking(this->mRocking - offsetRocking);
}

