#include "Manager.h"

//*************************************************************
// Init static
//*************************************************************
Manager* Manager::mInstance = NULL;


//*************************************************************
// Constructor - Destructor
//*************************************************************
Manager::Manager(void)
{
	this->mConfig = NULL;
}

Manager::~Manager(void)
{
	this->deleteConfig();
}


//*************************************************************
// Getters - Setters
//*************************************************************
ManagerConfig* Manager::getConfig()
{
	return this->mConfig;
}

void Manager::setConfig( ManagerConfig* p_config )
{
	this->deleteConfig();
	this->mConfig = p_config;
}

Manager* Manager::getInstance()
{
	if(Manager::mInstance == NULL)
		Manager::mInstance = new Manager();
	
	return Manager::mInstance;
}


//*************************************************************
// Methods
//*************************************************************
void Manager::deleteConfig()
{
	if(this->mConfig != NULL)
	{
		delete this->mConfig;
		this->mConfig = NULL;
	}
}
