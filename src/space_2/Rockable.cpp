#include "Rockable.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Rockable::Rockable(void)
{
	this->mRocking = 0;
	this->setRockingActived(true);
}

Rockable::~Rockable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int Rockable::getRocking()
{
	return this->mRocking;
}

bool Rockable::isRockingActived()
{
	return this->mRockingActived;
}

void Rockable::setRockingActived( bool p_actived )
{
	this->mRockingActived = p_actived;
}


//*************************************************************
// Methods
//*************************************************************
void Rockable::update()
{
	if(this->isRockingActived())
		this->updateRocking();
}

void Rockable::updateRocking()
{
	// Update clock
	float elapsedTime = this->mRockingClock.getElapsedTimeAsSeconds();
	if(elapsedTime > ROCKING_CYCLE)
	{
		this->mRockingClock.restart();
		elapsedTime = 0;
	}

	// Set new rocking
	if( elapsedTime < ROCKING_CYCLE_DEMI)
		this->mRocking = elapsedTime / ROCKING_PERIOD;
	else
		this->mRocking = ROCKING_CYCLE_DEMI_OFFSET - ((elapsedTime - ROCKING_CYCLE_DEMI) / ROCKING_PERIOD);
}