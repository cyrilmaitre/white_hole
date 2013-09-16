#include "NetworkJob.h"
#include "NetworkJobManager.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
NetworkJob::NetworkJob(void)
{
	this->mJobThread = NULL;
	this->mRunning = false;
	this->mLaunched = false;
	this->mJobThread = new sf::Thread(&NetworkJob::job, this);
}

NetworkJob::~NetworkJob(void)
{
	if(this->mJobThread != NULL)
		delete this->mJobThread;
}


//*************************************************************
// Getters - Setters
//*************************************************************
sf::Thread* NetworkJob::getJobThread()
{
	return this->mJobThread;
}

void NetworkJob::setJobThread( sf::Thread* p_job )
{
	this->mJobThread = p_job;
}

bool NetworkJob::isRunning()
{
	return this->mRunning;
}

void NetworkJob::setRunning( bool p_running )
{
	this->mRunning = p_running;
}

bool NetworkJob::isLaunched()
{
	return this->mLaunched;
}

void NetworkJob::setLaunched( bool p_launched )
{
	this->mLaunched = p_launched;
}

bool NetworkJob::isFinished()
{
	return this->isLaunched() && (!this->mRunning || this->mClock.getElapsedTimeAsSeconds() > NETWORKJOB_MAX_LIFE);
}


//*************************************************************
// Methods
//*************************************************************
void NetworkJob::launch()
{
	this->mLaunched = true;
	this->mRunning = true;
	this->mClock.restart();
	this->mJobThread->launch();
}


