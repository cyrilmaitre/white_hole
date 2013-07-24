#include "CloudWreckModelFactory.h"


//*************************************************************
// Init Static
//*************************************************************
CloudWreckModelFactory* CloudWreckModelFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
CloudWreckModelFactory::CloudWreckModelFactory(void)
{
}

CloudWreckModelFactory::~CloudWreckModelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
CloudWreckModel * CloudWreckModelFactory::getCloudWreckModel( std::string p_configName, bool p_useLoaded )
{
	CloudWreckModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new CloudWreckModel(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

CloudWreckModel * CloudWreckModelFactory::getCloudWreckModel( long p_id, bool p_useLoaded )
{
	return this->getCloudWreckModel(CLOUDWRECKMODEL_CONFIG + Tools::buildStringWithLong(p_id), p_useLoaded);
}
