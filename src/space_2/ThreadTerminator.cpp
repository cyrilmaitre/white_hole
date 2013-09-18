#include "ThreadTerminator.h"


//*************************************************************
// Define
//*************************************************************
#define UPDATE_TICK		1 // Sec


//*************************************************************
// Constructor - Destructor
//*************************************************************
ThreadTerminator::ThreadTerminator(void)
{
	this->mRunning = true;
	this->mThreadTerminator = new sf::Thread(&ThreadTerminator::update, this);
	this->mThreadTerminator->launch();
}

ThreadTerminator::~ThreadTerminator(void)
{
	this->setRunning(false);
	delete this->mThreadTerminator;
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool ThreadTerminator::isRunning()
{
	sf::Lock lock(this->mMutex);

	return this->mRunning;
}

void ThreadTerminator::setRunning( bool p_value )
{
	sf::Lock lock(this->mMutex);

	this->mRunning = p_value;
}

int ThreadTerminator::getTerminableCount()
{
	sf::Lock lock(this->mMutex);

	return this->mTerminables.size();
}


//*************************************************************
// Methods
//*************************************************************
void ThreadTerminator::addTerminable( Terminable* p_terminable )
{
	sf::Lock lock(this->mMutex);

	this->mTerminables.push_back(p_terminable);
}

Terminable* ThreadTerminator::removeTerminable( int p_index )
{
	sf::Lock lock(this->mMutex);

	Terminable* returnValue = this->mTerminables[p_index];
	this->mTerminables.erase(this->mTerminables.begin() + p_index);
	return returnValue;
}

void ThreadTerminator::update()
{
	while(this->isRunning())
	{
		sf::sleep(sf::seconds(UPDATE_TICK));
		while(this->getTerminableCount() > 0)
		{
			Terminable* currentTerminable = this->removeTerminable(0);
			if(currentTerminable != NULL)
			{
				currentTerminable->terminate(!this->isRunning());
				delete currentTerminable;
			}
		}
	}
}

