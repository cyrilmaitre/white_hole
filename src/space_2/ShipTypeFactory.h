#pragma once
#include "ShipType.h"
#include "Factory.h"

class ShipType;

// Define
#define SHIPTYPE_CONFIG		"shiptype-"

class ShipTypeFactory: public Factory<ShipType>
{
public:
	// Constructor - Destructor
	ShipTypeFactory(void);
	~ShipTypeFactory(void);

	// Methods
	ShipType* getShipType(std::string p_configShipType, bool p_useLoaded = true);
	ShipType* getShipType(int p_id, bool p_useLoaded = true);

	// Static
	static ShipTypeFactory* mInstance;
};

