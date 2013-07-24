#include "BackgroundSpaceManager.h"
#include "Sector.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDSPACESECTOR_COUNT	2


//*************************************************************
// Init static 
//*************************************************************
BackgroundSpaceManager* BackgroundSpaceManager::mInstance = NULL;


//*************************************************************
// Constructor - Destructor
//*************************************************************
BackgroundSpaceManager::BackgroundSpaceManager(void)
{
	this->mBackgroundSpaceScreen = NULL;

	for(int i = 0; i < BACKGROUNDSPACESECTOR_COUNT; i++)
		this->mBackgroundSpaceSectorPool.push_back(BackgroundGeneration::getBackgroundSpace(sf::Vector2i(SECTOR_WIDTH, SECTOR_HEIGHT)));

	this->notifyAppSizeChanged();
}

BackgroundSpaceManager::~BackgroundSpaceManager(void)
{
	if(this->mBackgroundSpaceScreen != NULL)
		delete this->mBackgroundSpaceScreen;

	for(int i = 0; i < this->mBackgroundSpaceSectorPool.size(); i++)
		delete this->mBackgroundSpaceSectorPool[i];
}


//*************************************************************
// Getters - Setters
//*************************************************************
BackgroundSpaceManager* BackgroundSpaceManager::getInstance()
{
	return BackgroundSpaceManager::mInstance;
}

BackgroundSpace* BackgroundSpaceManager::getBackgroundSpaceScreen()
{
	return this->mBackgroundSpaceScreen;
}

BackgroundSpace* BackgroundSpaceManager::getBackgroundSpaceSector()
{
	return this->mBackgroundSpaceSectorPool[Tools::random(0, this->mBackgroundSpaceSectorPool.size() - 1)];
}


//*************************************************************
// Methods
//*************************************************************
void BackgroundSpaceManager::notifyAppSizeChanged()
{
	if(this->mBackgroundSpaceScreen != NULL)
		delete this->mBackgroundSpaceScreen;

	this->mBackgroundSpaceScreen = BackgroundGeneration::getBackgroundSpace(sf::Vector2i(Resource::resource->getViewUi()->getSize().x, Resource::resource->getViewUi()->getSize().y));
}

void BackgroundSpaceManager::init()
{
	BackgroundSpaceManager::mInstance = new BackgroundSpaceManager();
}

void BackgroundSpaceManager::uninit()
{
	delete BackgroundSpaceManager::mInstance;
}

