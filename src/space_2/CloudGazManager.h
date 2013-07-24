#pragma once
#include "CloudGazModel.h"
#include "CloudGaz.h"
#include "Sector.h"

// Define
#define CLOUDGAZMANAGER_CONFIG			"cloudgazmodel"
#define CLOUDGAZMANAGER_CONFIG_COUNT	"count"

class CloudGazManager
{
public:
	// Constructor - Destructor
	CloudGazManager(KeyValueFile* p_config);
	~CloudGazManager(void);

	// Getters - Setters
	int getCloudGazModelCount();
	void setCloudGazModelCount(int p_count);

	// Static
	static CloudGazManager *getInstance();
	static void init();
	static void uninit();

	// Methods
	CloudGazModel* getRandomModel();
	CloudGaz* generateCloudGaz(Sector* p_sector);


private:
	// Attributs
	int mCloudGazModelCount;

	// Static
	static CloudGazManager* mInstance;
};

