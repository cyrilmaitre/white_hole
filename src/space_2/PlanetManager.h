#pragma once
#include "KeyValueFile.h"
#include "PlanetModelFactory.h"
#include "Planet.h"
#include "Sector.h"

// Define
#define PLANETMANAGER_CONFIG				"planetmodel"
#define PLANETMANAGER_CONFIG_COUNT			"count"

class PlanetManager
{
public:
	// Constructor - Destructor
	PlanetManager(KeyValueFile* p_config);
	~PlanetManager(void);

	// Getters - Setters
	int getPlanetModelCount();
	void setPlanetModelCount(int p_count);

	// Static
	static PlanetManager *getInstance();
	static void init();
	static void uninit();

	// Methods
	PlanetModel* getRandomModel();
	Planet* generatePlanet(Sector* p_sector);


private:
	// Attributs
	int mPlanetModelCount;

	// Static
	static PlanetManager* mInstance;
};

