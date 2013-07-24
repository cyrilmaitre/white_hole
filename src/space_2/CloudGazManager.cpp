#include "CloudGazManager.h"
#include "FactoryGet.h"
#include "ToolsImage.h"
#include "ToolsMap.h"


//************************************************************
// Define
//************************************************************
#define SHADE_INDICE	20


//*************************************************************
// Init static
//*************************************************************
CloudGazManager* CloudGazManager::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
CloudGazManager::CloudGazManager( KeyValueFile* p_config )
{
	this->setCloudGazModelCount(p_config->getInt(CLOUDGAZMANAGER_CONFIG_COUNT));
}

CloudGazManager::~CloudGazManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int CloudGazManager::getCloudGazModelCount()
{
	return this->mCloudGazModelCount;
}

void CloudGazManager::setCloudGazModelCount( int p_count )
{
	this->mCloudGazModelCount = p_count;
}


//*************************************************************
// Methods
//*************************************************************
CloudGazModel* CloudGazManager::getRandomModel()
{
	return FactoryGet::getCloudGazModelFactory()->getCloudGazModel(Tools::random(1, this->getCloudGazModelCount()));
}

CloudGaz* CloudGazManager::generateCloudGaz( Sector* p_sector )
{
	CloudGaz* generatedCloudGaz = new CloudGaz();

	generatedCloudGaz->setRotation(Tools::random(0, 360));
	generatedCloudGaz->setCloudColor(ToolsImage::shadeColor(ToolsMap::convertSectorColor(p_sector->getSectorColor()), SHADE_INDICE));
	generatedCloudGaz->setCloudModel(this->getRandomModel());

	return generatedCloudGaz;
}


//*************************************************************
// Static
//*************************************************************
CloudGazManager * CloudGazManager::getInstance()
{
	return CloudGazManager::mInstance;
}

void CloudGazManager::init()
{
	CloudGazManager::mInstance = new CloudGazManager(Resource::resource->getConfig(CLOUDGAZMANAGER_CONFIG));
}

void CloudGazManager::uninit()
{
	delete CloudGazManager::mInstance;
}


