#pragma once
#include "NpcType.h"
#include "Factory.h"

// Define
#define NPCTYPE_CONFIG		"npctype-"

class NpcTypeFactory: public Factory<NpcType>
{
public:
	// Constructor - Destructor
	NpcTypeFactory(void);
	~NpcTypeFactory(void);

	// Methods
	NpcType *getNpcType(std::string p_configName, bool p_useLoaded = true);
	NpcType *getNpcType(long p_jobId, bool p_useLoaded = true);

	// Static
	static NpcTypeFactory *mInstance;
};

