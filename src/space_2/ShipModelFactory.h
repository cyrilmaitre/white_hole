#pragma once
#include "Resource.h"
#include "ShipModel.h"
#include "Factory.h"

class ShipModel;

// Define
#define SHIPMODEL_CONFIG	"shipmodel-"

class ShipModelFactory: public Factory<ShipModel>
{
public:
	// Constructor - Destructor
	ShipModelFactory(void);
	~ShipModelFactory(void);

	// Methods
	ShipModel* getShipModel(std::string p_configShipModel, bool p_useLoaded = true);
	ShipModel* getShipModel(long p_id, bool p_useLoaded = true);

	// Static
	static ShipModelFactory *mInstance;
};

	