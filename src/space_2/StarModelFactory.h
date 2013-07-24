#pragma once
#include "Factory.h"
#include "StarModel.h"


class StarModelFactory : public Factory<StarModel>
{
public:
	// Constructor - Destructor
	StarModelFactory(void);
	~StarModelFactory(void);

	// Methods
	StarModel *getStarModel(std::string p_configName, bool p_useLoaded = true);
	StarModel *getStarModel(long p_id, bool p_useLoaded = true);

	// Static
	static StarModelFactory *mInstance;
};

