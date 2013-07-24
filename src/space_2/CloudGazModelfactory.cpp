#include "CloudGazModelfactory.h"


//*************************************************************
// Init Static
//*************************************************************
CloudGazModelfactory * CloudGazModelfactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
CloudGazModelfactory::CloudGazModelfactory(void)
{
}

CloudGazModelfactory::~CloudGazModelfactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
CloudGazModel * CloudGazModelfactory::getCloudGazModel( std::string p_configName, bool p_useLoaded  )
{
	CloudGazModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new CloudGazModel(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

CloudGazModel * CloudGazModelfactory::getCloudGazModel( long p_id, bool p_useLoaded )
{
	return this->getCloudGazModel(CLOUDGAZMODEL_CONFIG + Tools::buildStringWithLong(p_id), p_useLoaded);
}
