#include "StationModelFactory.h"


//*************************************************************
// Init Static
//*************************************************************
StationModelFactory * StationModelFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationModelFactory::StationModelFactory(void)
{
}


StationModelFactory::~StationModelFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
StationModel * StationModelFactory::getStationModel( std::string p_configName, bool p_useLoaded )
{	
	StationModel* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new StationModel(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

StationModel * StationModelFactory::getStationModel( long p_id, bool p_useLoaded )
{
	return this->getStationModel(STATIONMODEL_CONFIG + Tools::buildStringWithLong(p_id), p_useLoaded);
}
