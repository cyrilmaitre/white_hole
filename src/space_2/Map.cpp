#include "Map.h"
#include "Camera.h"
#include "DangerLevelManager.h"
#include "Game.h"
#include "PlanetManager.h"
#include "CloudGazManager.h"
#include "CloudWreckManager.h"
#include "AutoManager.h"
#include "ParticleManager.h"
#include "AnimationManager.h"
#include "WreckManager.h"
#include "StarManager.h"
#include "StationManager.h"
#include "FactoryGet.h"
#include "MapObject.h"

using namespace std;
using namespace sf;


//*************************************************************
// Define
//*************************************************************
#define SECTOR_STAR_COUNTMIN	0
#define SECTOR_STAR_COUNTMAX	1


//*************************************************************
// Init static
//*************************************************************
std::vector<BackgroundSpace*> Map::mBackgroundSpacePool;


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Map::Map(void)
{
	// Init sectors
	this->mSectors = new Sector**[MAP_SECTORS_TAB_SIZE];

	for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
	{
		this->mSectors[i] = new Sector*[MAP_SECTORS_TAB_SIZE];
	}

	for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
	{
		for(int j = 0; j < MAP_SECTORS_TAB_SIZE; j++)
		{
			this->mSectors[i][j] = NULL;
		}
	}

	// Init sectors Position
	this->mTopLeftSectorId = sf::Vector2i(0, 0);

	// Init npc ship spawner
	this->mNpcShipSpawner = new NpcShipSpawner();

	// Start update station
	StationManager::getInstance()->startUpdateThread();
}


Map::~Map(void)
{
	// Stop update station
	StationManager::getInstance()->stopUpdateThread();

	// Delete sector tab
	for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
	{
		delete this->mSectors[i];
	}
	delete this->mSectors;

	// Delete sectorsLoaded map
	for( map<sf::Vector2i, Sector*, Vector2iComparer>::iterator it = this->mSectorsLoaded.begin() ; it != this->mSectorsLoaded.end(); it++ )
	{
		if(it->second != NULL)
		{
			delete it->second;
		}
	}

	// Delete npc ship spawner
	delete this->mNpcShipSpawner;
}


//*************************************************************
// Getters - Setters
//*************************************************************
sf::Vector2i Map::getTopLeftSectorId()
{
	return this->mTopLeftSectorId;
}

void Map::setTopLeftSectorId( sf::Vector2i p_position )
{
	this->mTopLeftSectorId.x = p_position.x;
	this->mTopLeftSectorId.y = p_position.y;
}

Sector* Map::getSector( sf::Vector2i idSector, bool p_generateIfNull )
{
	std::map<sf::Vector2i, Sector*, Vector2iComparer>::iterator it;
	it = this->mSectorsLoaded.find(idSector);

	if(it != this->mSectorsLoaded.end())
	{
		return it->second;
	}
	else
	{
		if(p_generateIfNull)
		{
			// Generate new sector, save it and return it
			Sector* tmpSector = this->generateSector(idSector);
			return tmpSector;
		}
	}

	return NULL;
}

Sector* Map::getSector( int p_idX, int p_idY, bool p_generateIfNull )
{
	return this->getSector(sf::Vector2i(p_idX, p_idY), p_generateIfNull);
}

Sector* Map::getCurrentSector()
{
	double positionX = (int)Game::game->getShipPiloted()->getX(SECTOR_PLANE);
	double positionY = (int)Game::game->getShipPiloted()->getY(SECTOR_PLANE);

	int positionSectorX = positionX / SECTOR_WIDTH;
	int positionSectorY = positionY / SECTOR_HEIGHT;

	if(positionX < 0) positionSectorX--;
	if(positionY < 0) positionSectorY--;

	return this->getSector(positionSectorX, positionSectorY, true);	
}

int Map::getSectorsLoadedNumber()
{
	return this->mSectorsLoaded.size();
}

NpcShipSpawner * Map::getNpcShipSpawner()
{
	return this->mNpcShipSpawner;
}

void Map::setNpcShipSpawner( NpcShipSpawner *p_spawner )
{
	this->mNpcShipSpawner = p_spawner;
}

MapObjectSelector* Map::getMapObjectSelector()
{
	return &this->mMapObjectSelector;
}

std::vector<Sector*> Map::getAdjacentSectors( Sector* p_sector, std::vector<Sector*>& p_list )
{
	Sector* tmpSector = NULL;
	
	for(int i  = 0; i < 8; i++)
	{
		tmpSector = this->getSector(p_sector->getAdjacentSectorId(i), false);
		if(tmpSector != NULL)
			p_list.push_back(tmpSector);
	}

	return p_list;
}


//*************************************************************
// Method
//*************************************************************
Sector* Map::generateSector(sf::Vector2i p_idSector)
{
	Sector* tmpSector = new Sector(p_idSector);

	// Sum & count of dl adjacent
	std::vector<Sector*> listSector;
	this->getAdjacentSectors(tmpSector, listSector);
	int dangerLevelCount = 0;
	int dangerLevelSum = 0;

	for(int i = 0; i < listSector.size(); i++)
	{
		dangerLevelCount++;
		dangerLevelSum += listSector[i]->getDangerLevel()->getDangerLevel();
	}

	// Danger Level
	tmpSector->setDangerLevel(DangerLevelManager::getInstance()->generateDangerLevel(dangerLevelCount, dangerLevelSum));

	// Planets
	int planetCount = tmpSector->getDangerLevel()->generatePlanetCount();
	tmpSector->setPlanetsCount(planetCount);
	if(planetCount > 0)
	{
		for(int i = 0; i < planetCount; i++)
		{
			Planet* currentPlanet = PlanetManager::getInstance()->generatePlanet(tmpSector);
			if(currentPlanet != NULL)
				tmpSector->addMapObject(currentPlanet, true);
		}
	}

	// Cloud Gazs
	int cloudgazCount = tmpSector->getDangerLevel()->generateCloudGazCount();
	tmpSector->setCloudGazsCount(cloudgazCount);
	if(cloudgazCount > 0)
	{
		for(int i = 0; i < cloudgazCount; i++)
		{
			CloudGaz* currentCloudGaz = CloudGazManager::getInstance()->generateCloudGaz(tmpSector);
			if(currentCloudGaz != NULL)
				tmpSector->addMapObject(currentCloudGaz);
		}
	}

	// Cloud Wrecks
	int cloudWreckCount = tmpSector->getDangerLevel()->generateCloudWreckCount();
	tmpSector->setCloudWrecksCount(cloudWreckCount);
	if(cloudWreckCount > 0)
	{
		for(int i = 0; i < cloudWreckCount; i++)
		{
			CloudWreck* currentCloudWreck = CloudWreckManager::getInstance()->generateCloudWreck(tmpSector);
			if(currentCloudWreck != NULL)
				tmpSector->addMapObject(currentCloudWreck);
		}
	}

	// Star
	int starCount = Tools::random(SECTOR_STAR_COUNTMIN, SECTOR_STAR_COUNTMAX);
	if(starCount > 0)
	{
		for(int i = 0; i < starCount; i++)
		{
			Star* currenStar = StarManager::getInstance()->generateStar(tmpSector);
			if(currenStar != NULL)
				tmpSector->addMapObject(currenStar, true);
		}
	}

	// Npc Station
	int stationCount = tmpSector->getDangerLevel()->generateStationCount();
	if(stationCount > 0)
	{
		for(int i = 0; i < stationCount; i++)
		{
			Station* currenStation = StationManager::getInstance()->generateStation(tmpSector);
			if(currenStation != NULL)
				tmpSector->addEntity(currenStation);
		}
	}
	if(tmpSector->getIdSectorX() == 0 && tmpSector->getIdSectorY() == 0)	// Spawn station good agressive at charactership's start position
	{
		Station* goodStation = StationManager::getInstance()->generateStation(tmpSector);
		goodStation->setNpcType(FactoryGet::getNpcTypeFactory()->getNpcType(1));
		Vector2f goodStationPosition = MapObject::convertPosition(sf::Vector2f((float)(SECTOR_WIDTH / 2), (float)(SECTOR_HEIGHT / 2)), SECTOR_PLANE, STATION_PLANE);
		goodStation->setPosition(goodStationPosition.x, goodStationPosition.y);
		tmpSector->addEntity(goodStation, false);
	}

	this->addSector(tmpSector);
	return tmpSector;
}

void Map::addSector( Sector* p_sector )
{
	// Check if sector exist
	bool isSectorExist = false;
	std::map<sf::Vector2i, Sector*, Vector2iComparer>::iterator it;
	it = this->mSectorsLoaded.find(p_sector->getIdSector());

	if(it != this->mSectorsLoaded.end())
		isSectorExist = true;

	// Set
	if(isSectorExist)
	{
		if(it->second != NULL)
			delete it->second;
		it->second = p_sector;
	}
	else
	{
		this->mSectorsLoaded.insert(std::pair<sf::Vector2i, Sector*>(p_sector->getIdSector(), p_sector));
	}
}

void Map::draw()
{
	// Draw sector
	Resource::resource->selectView(RESOURCE_ID_VIEW_MAP, SECTOR_PLANE);
	for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
	{
		for(int j = 0; j < MAP_SECTORS_TAB_SIZE; j++)
		{
			this->mSectors[i][j]->draw();
		}
	}

	// Draw sector object
	for(int p = MapObject::getPlaneBackground(); p >= MapObject::getPlaneForeground(); p--)
	{
		Resource::resource->selectView(RESOURCE_ID_VIEW_MAP, p);
		for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
		{
			for(int j = 0; j < MAP_SECTORS_TAB_SIZE; j++)
			{
				this->mSectors[i][j]->drawMapObjects(p);
				this->mSectors[i][j]->drawEntities(p);
			}
		}
	}

	// Draw wrecks
	Resource::resource->selectView(RESOURCE_ID_VIEW_MAP, CAMERA_PLANE);
	WreckManager::draw();

	// Draw Particles
	Resource::resource->selectView(RESOURCE_ID_VIEW_UI);
	ParticleManager::draw();
	Resource::resource->selectView(RESOURCE_ID_VIEW_MAP);

	// Draw spawner
	this->getNpcShipSpawner()->draw();
	
	// Draw Ship
	Game::game->getShipPiloted()->draw();

	// Draw AutoManager
	AutoManager::draw();

	// Draw star dazzle
	Resource::resource->selectView(RESOURCE_ID_VIEW_MAP, STAR_PLANE);
	for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
	{
		for(int j = 0; j < MAP_SECTORS_TAB_SIZE; j++)
		{
			for(int h = 0; h < this->mSectors[i][j]->getStarCount(); h++)
			{
				this->mSectors[i][j]->getStar(h)->drawDazzle();
			}
		}
	}
	Resource::resource->selectView(RESOURCE_ID_VIEW_UI);
}

void Map::update()
{
	// Update sectors (gen)
	sf::Vector2i tmpTopLeftSectorId = this->calculateTopLeftSectorId();
	if(this->mTopLeftSectorId != tmpTopLeftSectorId)
	{
		this->setTopLeftSectorId(tmpTopLeftSectorId);

		// Set visible false
		for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
		{
			for(int j = 0; j < MAP_SECTORS_TAB_SIZE; j++)
			{
				if(this->mSectors[i][j] != NULL)
					this->mSectors[i][j]->setVisible(false);
			}
		}

		// Update
		for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
		{
			for(int j = 0; j < MAP_SECTORS_TAB_SIZE; j++)
			{
				this->mSectors[i][j] = this->getSector(this->mTopLeftSectorId.x + i, this->mTopLeftSectorId.y + j, true);
			}
		}

		// Set visible true
		for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
		{
			for(int j = 0; j < MAP_SECTORS_TAB_SIZE; j++)
			{
				if(this->mSectors[i][j] != NULL)
					this->mSectors[i][j]->setVisible(true);
			}
		}
	}	

	// Update spawner
	this->getNpcShipSpawner()->update();

	// Update wrecks
	WreckManager::update();

	// Update sectors
	for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
	{
		for(int j = 0; j < MAP_SECTORS_TAB_SIZE; j++)
		{
			// Update sector
			this->mSectors[i][j]->update();
		}
	}

	// Update star dazzle
	for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
	{
		for(int j = 0; j < MAP_SECTORS_TAB_SIZE; j++)
		{
			for(int h = 0; h < this->mSectors[i][j]->getStarCount(); h++)
			{
				this->mSectors[i][j]->getStar(h)->updateDazzle();
			}
		}
	}

	// Update visited
	this->getCurrentSector()->setVisited(true);

	// Update object selector
	this->getMapObjectSelector()->update();
}

void Map::update( sf::Event p_event )
{
	// Update spawner
	this->getNpcShipSpawner()->update(p_event);

	// Update Wreck
	WreckManager::update(p_event);

	// Update sectors
	for(int i = 0; i < MAP_SECTORS_TAB_SIZE; i++)
	{
		for(int j = 0; j < MAP_SECTORS_TAB_SIZE; j++)
		{
			if(this->mSectors[i][j] != NULL)
				this->mSectors[i][j]->update(p_event);
		}
	}
}

sf::Vector2i Map::calculateTopLeftSectorId()
{
	sf::Vector2i sectorsPosition;
	Sector* currentSector = this->getCurrentSector();

	sectorsPosition.x = currentSector->getIdSectorX() - (MAP_SECTORS_TAB_SIZE / 2);
	sectorsPosition.y = currentSector->getIdSectorY() - (MAP_SECTORS_TAB_SIZE / 2);

	return sectorsPosition;
}


