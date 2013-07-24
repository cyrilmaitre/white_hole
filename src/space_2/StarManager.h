#pragma once
#include "Sector.h"
#include "Star.h"
#include "StarModel.h"

class StarManager
{
public:
	// Constructor - Destructor
	StarManager(KeyValueFile* p_config);
	~StarManager(void);

	// Getters - Setters
	int getStarModelCount();
	void setStarModelCount(int p_count);

	// Methods
	StarModel* getRandomModel();
	Star* generateStar(Sector* p_sector);

	// Static
	static StarManager *getInstance();
	static void init();
	static void uninit();


private:
	// Attributs
	int mStarModelCount;

	// Static
	static StarManager* mInstance;
};

