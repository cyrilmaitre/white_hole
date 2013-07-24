#pragma once
#include "Factory.h"
#include "StationModel.h"

// Define
#define STATIONMODEL_CONFIG		"stationmodel-"

class StationModelFactory : public Factory<StationModel>
{
public:
	// Constructor - Destructor
	StationModelFactory(void);
	~StationModelFactory(void);

	// Methods
	StationModel *getStationModel(std::string p_configName, bool p_useLoaded = true);
	StationModel *getStationModel(long p_id, bool p_useLoaded = true);

	// Static
	static StationModelFactory *mInstance;
};

