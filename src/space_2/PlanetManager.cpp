#include "PlanetManager.h"
#include "FactoryGet.h"
#include "SplitString.h"


//*************************************************************
// Init static
//*************************************************************
PlanetManager* PlanetManager::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
PlanetManager::PlanetManager(KeyValueFile* p_config)
{
	this->setPlanetModelCount(p_config->getInt(PLANETMANAGER_CONFIG_COUNT));
}

PlanetManager::~PlanetManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int PlanetManager::getPlanetModelCount()
{
	return this->mPlanetModelCount;
}

void PlanetManager::setPlanetModelCount( int p_count )
{
	this->mPlanetModelCount = p_count;
}


//*************************************************************
// Methods
//*************************************************************
PlanetManager * PlanetManager::getInstance()
{
	return PlanetManager::mInstance;
}

void PlanetManager::init()
{
	PlanetManager::mInstance = new PlanetManager(Resource::resource->getConfig(PLANETMANAGER_CONFIG));
}

void PlanetManager::uninit()
{
	delete PlanetManager::mInstance;
}

PlanetModel* PlanetManager::getRandomModel()
{
	return FactoryGet::getPlanetModelFactory()->getPlanetModel(Tools::random(1, this->getPlanetModelCount()));
}

Planet* PlanetManager::generatePlanet( Sector* p_sector )
{
	Planet* generatedPlanet = new Planet();

	generatedPlanet->setRotation(Tools::random(0, 360));
	generatedPlanet->setPlanetModel(this->getRandomModel());

	return generatedPlanet;
}

