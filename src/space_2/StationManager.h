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

	// Static
	static StationManager *getInstance();
	static void init();
	static void uninit();

	// Methods
	StationModel* getRandomModel();
	Station* generateStation(Sector* p_sector);


private:
	// Attributs
	int mStationModelCount;

	// Static
	static StationManager* mInstance;
};

