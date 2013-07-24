#include "Effect.h"


//******************************
// Constructor - Destructor
//******************************
Effect::Effect(void)
{
	this->mLiveTime = 0;
}

Effect::~Effect(void)
{
}


//******************************
// Constructor - Destructor
//******************************
long Effect::getLiveTime()
{
	return this->mLiveTime;
}

void Effect::setLiveTime( long p_lifeTime )
{
	this->mLiveTime = p_lifeTime;
}


bool Effect::isFinished()
{
	return this->mClockAuto.getElapsedTimeAsMilliseconds() > this->getLiveTime();
}

void Effect::update()
{

}

void Effect::draw()
{

}
