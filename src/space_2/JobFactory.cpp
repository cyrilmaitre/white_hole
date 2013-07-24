#include "JobFactory.h"


//*************************************************************
// Init static 
//*************************************************************
JobFactory * JobFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
JobFactory::JobFactory(void)
{
}

JobFactory::~JobFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
Job* JobFactory::getJobMercenary()
{
	return this->getJob(JOB_CONFIG_MERCENARY);
}

Job* JobFactory::getJobIndustrialist()
{
	return this->getJob(JOB_CONFIG_INDUSTRIALIST);
}

Job* JobFactory::getJobTrader()
{
	return this->getJob(JOB_CONFIG_TRADER);
}

Job* JobFactory::getJobBuilder()
{
	return this->getJob(JOB_CONFIG_BUILDER);
}

Job* JobFactory::getJob( std::string p_configName, bool p_useLoaded )
{
	Job* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new Job(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

Job* JobFactory::getJob( long p_jobId, bool p_useLoaded )
{
	return this->getJob(JOB_CONFIG+Tools::buildStringWithLong(p_jobId), p_useLoaded);
}
