#include "CloudWreckManager.h"
#include "FactoryGet.h"


//*************************************************************
// Degine
//*************************************************************
#define CLOUDWRECKMANAGER_VALIDATECOUNT_MAX		5


//*************************************************************
// Init static
//*************************************************************
CloudWreckManager* CloudWreckManager::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
CloudWreckManager::CloudWreckManager(KeyValueFile* p_config)
{
	this->setCloudWreckModelCount(p_config->getInt(CLOUDWRECKMANAGER_CONFIG_COUNT));
}

CloudWreckManager::~CloudWreckManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int CloudWreckManager::getCloudWreckModelCount()
{
	return this->mCloudWreckModelCount;
}

void CloudWreckManager::setCloudWreckModelCount( int p_count )
{
	this->mCloudWreckModelCount = p_count;
}


//*************************************************************
// Methods
//*************************************************************
CloudWreckModel* CloudWreckManager::getRandomModel()
{
	return FactoryGet::getCloudWreckModelFactory()->getCloudWreckModel(Tools::random(1, this->getCloudWreckModelCount()));
}

CloudWreck* CloudWreckManager::generateCloudWreck( Sector* p_sector )
{
	CloudWreck* generatedCloudWreck = new CloudWreck();

	generatedCloudWreck->setRotation(Tools::random(0, 360));
	generatedCloudWreck->setCloudModel(this->getRandomModel());

	return generatedCloudWreck;
}


//*************************************************************
// Static
//*************************************************************
CloudWreckManager * CloudWreckManager::getInstance()
{
	return CloudWreckManager::mInstance;
}

void CloudWreckManager::init()
{
	CloudWreckManager::mInstance = new CloudWreckManager(Resource::resource->getConfig(CLOUDWRECKMANAGER_CONFIG));
}

void CloudWreckManager::uninit()
{
	delete CloudWreckManager::mInstance;
}


