#pragma once
#include "MapObjectModel.h"


class CloudGazModel : public MapObjectModel
{
public:
	// Constructor - Destructor
	CloudGazModel(KeyValueFile* p_config);
	~CloudGazModel(void);
};

