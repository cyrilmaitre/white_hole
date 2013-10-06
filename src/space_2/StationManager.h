#pragma once
#include "StationModel.h"
#include "Station.h"
#include "Sector.h"

// Define
#define STATIONMANAGER_CONFIG			"stationmodel"
#define STATIONMANAGER_CONFIG_COUNT		"count"

class StationManager
{
public:
	// Constructor - Destructor
	StationManager(KeyValueFile* p_config);
	~StationManager(void);

	// Getters - Setters
	int getStationModelCount();
	void setStationModelCount(int p_count);

	int getStationsCount();
	Station* getStation(int p_index);

	bool isUpdateStations();
	void setUpdateStations(bool p_value);

	// Static
	static StationManager *getInstance();
	static void init();
	static void uninit();

	// Methods
	StationModel* getRandomModel();
	Station* generateStation(Sector* p_sector);

	void addStation(Station* p_station);
	void removeStation(Station* p_station);
	void updateStocksAll();
	void updateStock(Station* p_station);

	void startUpdateThread();
	void stopUpdateThread();


private:
	// Attributs
	int mStationModelCount;

	std::vector<Station*> mStations;
	bool mUpdateStations;
	sf::Thread* mUpdateStationsThread;
	sf::Mutex mMutex;

	// Static
	static StationManager* mInstance;
};

