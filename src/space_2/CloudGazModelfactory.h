#pragma once
#include "Factory.h"
#include "CloudGazModel.h"

// Define
#define CLOUDGAZMODEL_CONFIG	"cloudgazmodel-"

class CloudGazModelfactory : public Factory<CloudGazModel>
{
public:
	// Constructor - Destructor
	CloudGazModelfactory(void);
	~CloudGazModelfactory(void);

	// Methods
	CloudGazModel *getCloudGazModel(std::string p_configName, bool p_useLoaded = true);
	CloudGazModel *getCloudGazModel(long p_id, bool p_useLoaded = true);

	// Static
	static CloudGazModelfactory *mInstance;
};

