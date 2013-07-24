#pragma once
#include "KeyValueFile.h"

// Define
#define STUFFABLEDATA_CONFIG_STUFFSLOTMAX	"stuff_slot"

class StuffableData
{
public:
	// Constructor - Destructor
	StuffableData(void);
	~StuffableData(void);

	// Getters - Setters
	virtual int getStuffSlotMax();
	void setStuffSlotMax(int p_slotMax);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromStuffableData(StuffableData* p_object);


protected:
	// Attributs
	int mStuffSlotMax;
};

