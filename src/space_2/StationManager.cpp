#include "StationManager.h"
#include "FactoryGet.h"
#include "FactoryGet.h"


//*************************************************************
// Init static
//*************************************************************
StationManager* StationManager::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationManager::StationManager(KeyValueFile* p_config)
{
	this->setStationModelCount(p_config->getInt(STATIONMANAGER_CONFIG_COUNT));
}

StationManager::~StationManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int StationManager::getStationModelCount()
{
	return this->mStationModelCount;
}

void StationManager::setStationModelCount( int p_count )
{
	this->mStationModelCount = p_count;
}


//*************************************************************
// Methods
//*************************************************************
StationManager * StationManager::getInstance()
{
	return StationManager::mInstance;
}

void StationManager::init()
{
	StationManager::mInstance = new StationManager(Resource::resource->getConfig(STATIONMANAGER_CONFIG));
}

void StationManager::uninit()
{
	delete StationManager::mInstance;
}

StationModel* StationManager::getRandomModel()
{
	//return FactoryGet::getStationModelFactory()->getStationModel(Tools::random(1, this->getStationModelCount()));
	return FactoryGet::getStationModelFactory()->getStationModel(9);
}

Station* StationManager::generateStation( Sector* p_sector )
{
	Station* generatedStation = new Station();

	generatedStation->setModel(this->getRandomModel());
	generatedStation->setNpcType(FactoryGet::getNpcTypeFactory()->getRandomNpcType());

	return generatedStation;
}
