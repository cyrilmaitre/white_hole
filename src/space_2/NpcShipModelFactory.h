#pragma once
#include "Factory.h"
#include "NpcShipModel.h"

// Define
#define NPCSHIPMODEL_CONFIG		"npcshipmodel-"

class NpcShipModelFactory: public Factory<NpcShipModel>
{
public:
	// Constructor - Destructor
	NpcShipModelFactory(void);
	~NpcShipModelFactory(void);

	// Methods
	NpcShipModel *getNpcShipModel(std::string p_configName, bool p_useLoaded = true);
	NpcShipModel *getNpcShipModel(long p_id, bool p_useLoaded = true);

	// Static
	static NpcShipModelFactory *mInstance;
};
 
