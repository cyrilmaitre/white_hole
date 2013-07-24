#include "Clock.h"
#include "ClockManager.h"

//*************************************************************
// Constructor - Destructor
//*************************************************************
mks::Clock::Clock(void)
{
	this->mElapsedTimeAsSeconds = 0;
	this->mTimeStartAsSeconds = 0;
	this->mElapsedTimeAsMilliseconds = 0;
	this->mTimeStartAsMilliseconds = 0;
	this->mLastIterationSeconds = -1;
	this->mLastIterationMilliseconds = -1;
	this->restart();
}

mks::Clock::~Clock(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
float mks::Clock::getElapsedTimeAsSeconds()
{
	if(this->mLastIterationSeconds != ClockManager::getIteration())
	{
		this->mElapsedTimeAsSeconds = ClockManager::getElapsedTimeAsSeconds() - this->mTimeStartAsSeconds;
		this->mLastIterationSeconds = ClockManager::getIteration();
	}

	return this->mElapsedTimeAsSeconds;
}

long mks::Clock::getElapsedTimeAsMilliseconds()
{
	if(this->mLastIterationMilliseconds != ClockManager::getIteration())
	{
		this->mElapsedTimeAsMilliseconds = ClockManager::getElapsedTimeAsMilliseconds() - this->mTimeStartAsMilliseconds;
		this->mLastIterationMilliseconds = ClockManager::getIteration();
	}

	return this->mElapsedTimeAsMilliseconds;
}


//*************************************************************
// Methods
//*************************************************************
void mks::Clock::restart()
{
	this->mLastIterationSeconds = ClockManager::getIteration();
	this->mLastIterationMilliseconds = ClockManager::getIteration();

	this->mTimeStartAsSeconds = ClockManager::getElapsedTimeAsSeconds();
	this->mElapsedTimeAsSeconds = 0;
	this->mTimeStartAsMilliseconds = ClockManager::getElapsedTimeAsMilliseconds();
	this->mElapsedTimeAsMilliseconds = 0;
}


