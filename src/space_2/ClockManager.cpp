#include "ClockManager.h"

//*************************************************************
// Init static
//*************************************************************
long ClockManager::mElapsedTimeAsMilliseconds = 0;
float ClockManager::mElapsedTimeAsSeconds = 0;
sf::Clock ClockManager::mClock;
long ClockManager::mIteration = 0;


//*************************************************************
// Constructor - Destructor
//*************************************************************
ClockManager::ClockManager(void)
{
}

ClockManager::~ClockManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
float ClockManager::getElapsedTimeAsSeconds()
{
	return ClockManager::mElapsedTimeAsSeconds;
}

long ClockManager::getElapsedTimeAsMilliseconds()
{
	return ClockManager::mElapsedTimeAsMilliseconds;
}

int ClockManager::getIteration()
{
	return ClockManager::mIteration;
}


//*************************************************************
// Methods
//*************************************************************
void ClockManager::update()
{
	sf::Time elapsedTime = ClockManager::mClock.getElapsedTime();
	ClockManager::mElapsedTimeAsSeconds = elapsedTime.asSeconds();
	ClockManager::mElapsedTimeAsMilliseconds = elapsedTime.asMilliseconds();
	ClockManager::mIteration++;
}