#include "NetworkJobManager.h"


//*************************************************************
// Static
//*************************************************************
NetworkJobManager* NetworkJobManager::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
NetworkJobManager::NetworkJobManager(void)
{
}

NetworkJobManager::~NetworkJobManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool NetworkJobManager::hasJob()
{
	return this->mJobs.size() > 0;
}

int NetworkJobManager::getJobCount()
{
	return this->mJobs.size();
}

int NetworkJobManager::getJobCountMax()
{
	return NETWORKJOB_MANAGER_MAX_JOB;
}


//*************************************************************
// Methods
//*************************************************************
void NetworkJobManager::init()
{
	NetworkJobManager::mInstance = new NetworkJobManager();
}

void NetworkJobManager::uninit()
{
	delete NetworkJobManager::mInstance;
}

NetworkJobManager* NetworkJobManager::getInstance()
{
	return NetworkJobManager::mInstance;
}

void NetworkJobManager::addJob( NetworkJob* p_job )
{
	if(this->mJobs.size() < NETWORKJOB_MANAGER_MAX_JOB)
		this->mJobs.push_back(p_job);
	else
		delete p_job;
}

void NetworkJobManager::removeJob( int p_position )
{
	delete this->mJobs[p_position];
	this->mJobs.erase(this->mJobs.begin() + p_position);
}

void NetworkJobManager::update()
{
	if(this->hasJob() && this->mJobs[0] != NULL)
	{
		if(this->mJobs[0]->isFinished())
			this->removeJob(0);
		else if(!this->mJobs[0]->isLaunched())
			this->mJobs[0]->launch();
	}
}

