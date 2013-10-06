#include "StationManager.h"
#include "FactoryGet.h"
#include "FactoryGet.h"

//*************************************************************
// Define
//*************************************************************
#define UPDATESTATIONS_SLEEP		500	// ms


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
	this->setUpdateStations(true);

	this->mUpdateStationsThread = NULL;
}

StationManager::~StationManager(void)
{
	if(this->mUpdateStationsThread != NULL)
		delete this->mUpdateStationsThread;
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

int StationManager::getStationsCount()
{
	sf::Lock lock(this->mMutex);
	return this->mStations.size();
}

Station* StationManager::getStation( int p_index )
{
	sf::Lock lock(this->mMutex);

	if(p_index < 0)
		p_index = 0;
	else if(p_index >= this->mStations.size())
		p_index = this->mStations.size() - 1;

	return this->mStations[p_index];
}

bool StationManager::isUpdateStations()
{
	sf::Lock lock(this->mMutex);
	return this->mUpdateStations;
}

void StationManager::setUpdateStations( bool p_value )
{
	sf::Lock lock(this->mMutex);
	this->mUpdateStations = p_value;
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
	return FactoryGet::getStationModelFactory()->getStationModel(Tools::random(1, this->getStationModelCount()));
}

Station* StationManager::generateStation( Sector* p_sector )
{
	Station* generatedStation = new Station();

	generatedStation->setModel(this->getRandomModel());
	generatedStation->setNpcType(FactoryGet::getNpcTypeFactory()->getRandomNpcType());

	return generatedStation;
}

void StationManager::addStation( Station* p_station )
{
	sf::Lock lock(this->mMutex);
	this->mStations.push_back(p_station);
}

void StationManager::removeStation( Station* p_station )
{
	sf::Lock lock(this->mMutex);
	for(int i = 0; i < this->mStations.size(); i++)
	{
		if(this->mStations[i]->getIdMapObject() == p_station->getIdMapObject())
		{
			this->mStations.erase(this->mStations.begin() + i);
			break;
		}
	}
}

void StationManager::updateStocksAll()
{
	while(this->isUpdateStations())
	{
		for(int i = 0; i < this->getStationsCount(); i++)
		{
			if(this->isUpdateStations())
				this->updateStock(this->getStation(i));
			else
				break;
		}
		sf::sleep(sf::milliseconds(UPDATESTATIONS_SLEEP));
	}
}

void StationManager::updateStock( Station* p_station )
{
	sf::Lock lock(this->mMutex);
	if(p_station->isUpdateStocksTime())
		p_station->updateStocks();
}

void StationManager::startUpdateThread()
{
	this->mUpdateStationsThread = new sf::Thread(&StationManager::updateStocksAll, this);
	this->mUpdateStationsThread->launch();
}

void StationManager::stopUpdateThread()
{
	this->setUpdateStations(false);
}


