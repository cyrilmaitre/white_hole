#pragma once
#include "Factory.h"
#include "CloudWreckModel.h"

// Define
#define CLOUDWRECKMODEL_CONFIG		"cloudwreckmodel-"

class CloudWreckModelFactory : public Factory<CloudWreckModel>
{
public:
	// Constructor - Destructor
	CloudWreckModelFactory(void);
	~CloudWreckModelFactory(void);

	// Methods
	CloudWreckModel *getCloudWreckModel(std::string p_configName, bool p_useLoaded = true);
	CloudWreckModel *getCloudWreckModel(long p_id, bool p_useLoaded = true);

	// Static
	static CloudWreckModelFactory* mInstance;
};

