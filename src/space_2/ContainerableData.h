#pragma once
#include "KeyValueFile.h"

// Define
#define CONTAIRABLEDATA_CONFIG_CARGOMAX		"cargo"

class ContainerableData
{
public:
	// Constructor - Destructor
	ContainerableData(void);
	~ContainerableData(void);

	// Getters - Setters
	int getCargoMax();
	virtual void setCargoMax(int p_cargoMax);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


protected:
	// Attributs
	int mCargoMax;
};

