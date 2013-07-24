#pragma once
#include "CloudWreckModel.h"
#include "CloudWreck.h"
#include "Sector.h"
#include "KeyValueFile.h"

// Define
#define CLOUDWRECKMANAGER_CONFIG			"cloudwreckmodel"
#define CLOUDWRECKMANAGER_CONFIG_COUNT		"count"

class CloudWreckManager
{
public:
	// Constructor - Destructor
	CloudWreckManager(KeyValueFile* p_config);
	~CloudWreckManager(void);

	// Getters - Setters
	int getCloudWreckModelCount();
	void setCloudWreckModelCount(int p_count);

	// Static
	static CloudWreckManager *getInstance();
	static void init();
	static void uninit();

	// Methods
	CloudWreckModel* getRandomModel();
	CloudWreck* generateCloudWreck(Sector* p_sector);


private:
	// Attributs
	int mCloudWreckModelCount;

	// Static
	static CloudWreckManager* mInstance;
};

