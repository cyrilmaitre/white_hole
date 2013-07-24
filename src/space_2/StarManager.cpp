#include "StarManager.h"
#include "ToolsImage.h"
#include "ToolsMap.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_NAME					"starmodel"
#define CONFIG_COUNT				"count"
#define STAR_RADIUS					128
#define STAR_SIZE_FACTOR_MIN		50		// %
#define STAR_SIZE_FACTOR_MAX		150		// %
#define STAR_COUNT					5
#define SHADE_INDICE				20


//*************************************************************
// Init static
//*************************************************************
StarManager* StarManager::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
StarManager::StarManager( KeyValueFile* p_config )
{
	this->setStarModelCount(p_config->getInt(CONFIG_COUNT));
}

StarManager::~StarManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int StarManager::getStarModelCount()
{
	return this->mStarModelCount;
}

void StarManager::setStarModelCount( int p_count )
{
	this->mStarModelCount = p_count;
}


//*************************************************************
// Methods
//*************************************************************
StarModel* StarManager::getRandomModel()
{
	return FactoryGet::getStarModelFactory()->getStarModel(Tools::random(1, this->getStarModelCount()));
}

Star* StarManager::generateStar( Sector* p_sector )
{
	Star* generatedStar = new Star();

	generatedStar->setRotation(Tools::random(0, 360));
	generatedStar->setDazzleColor(ToolsImage::shadeColor(ToolsMap::convertSectorColor(p_sector->getSectorColor()), SHADE_INDICE));
	generatedStar->setStarModel(this->getRandomModel());	

	return generatedStar;
}

StarManager * StarManager::getInstance()
{
	return StarManager::mInstance;
}

void StarManager::init()
{
	StarManager::mInstance = new StarManager(Resource::resource->getConfig(CONFIG_NAME));
}

void StarManager::uninit()
{
	delete StarManager::mInstance;
}

