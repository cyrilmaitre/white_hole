#include "Sector.h"
#include "Camera.h"
#include "Tools.h"
#include "BackgroundSpaceManager.h"
#include "PlanetManager.h"
#include "Game.h"
#include "Tools.h"
#include "ToolsImage.h"
#include "EntityManager.h"
#include "ToolsMap.h"


//*************************************************************
// Define
//*************************************************************
#define VALIDATECOUNT_MAX	10
#define COLORSPREAD_MIN		16
#define COLORSPREAD_MAX		24


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Sector::Sector( int p_x, int p_y )
{
	// Set with param
	this->mX = p_x;
	this->mY = p_y;

	// Calculate idSector
	this->calculateIdSector();

	// Init
	this->init();
}

Sector::Sector( sf::Vector2i p_idSector)
{
	// Set with param
	this->mIdSector = p_idSector;

	// Calculate position
	this->calculatePosition();

	// Init
	this->init();
}

void Sector::init()
{
	this->setPlanetsCount(0);
	this->setCloudGazsCount(0);
	this->setCloudWrecksCount(0);
	this->setVisible(false);
	this->setVisited(false);
	this->initSectorColor();

	this->mBackground = BackgroundSpaceManager::getInstance()->getBackgroundSpaceSector();
	this->mBackgroundSprite.setTexture(this->mBackground->getBackgroundTexture()->getTexture());
}

void Sector::initSectorColor()
{
	std::vector<Sector*> listSector;
	Game::game->getMap()->getAdjacentSectors(this, listSector);
	bool genSectorColor = true;

	for(int i = 0; i < listSector.size(); i++)
	{
		Sector* currentSector = listSector[i];
		if(currentSector->canSpreadSectorColor() && genSectorColor)
		{
			this->setSectorColor(currentSector->getSectorColor());
			currentSector->decSectorColorSpread();

			this->setSectorColorSpread(currentSector->getSectorColorSpread() / 2);
			currentSector->setSectorColorSpread(currentSector->getSectorColorSpread() - this->getSectorColorSpread());

			genSectorColor = false;
			break;
		}
	}

	if(genSectorColor)
	{
		this->setSectorColor(ToolsMap::getRandomSectorColor());
		this->setSectorColorSpread(Tools::random(COLORSPREAD_MIN, COLORSPREAD_MAX));
	}
}

Sector::~Sector(void)
{
	for(int i = 0; i < this->mObjects.size(); i++)
	{
		if(this->mObjects[i] != NULL)
			delete this->mObjects[i];
	}
}


//*************************************************************
// Getters - Setters
//*************************************************************
sf::Vector2i Sector::getIdSector()
{
	return this->mIdSector;
}

int Sector::getIdSectorX()
{
	return this->mIdSector.x;
}

int Sector::getIdSectorY()
{
	return this->mIdSector.y;
}

int Sector::getX()
{
	return this->mX;
}

int Sector::getY()
{
	return this->mY;
}

sf::Vector2i Sector::getPosition()
{
	return sf::Vector2i(this->getX(), this->getY());
}

DangerLevel* Sector::getDangerLevel()
{
	return this->mDangerLevel;
}

void Sector::setDangerLevel( DangerLevel* p_level )
{
	this->mDangerLevel = p_level;
}

BackgroundSpace* Sector::getBackground()
{
	return this->mBackground;
}

bool Sector::isVisible()
{
	return this->mVisible;
}

void Sector::setVisible( bool p_isVisible )
{
	bool notify = p_isVisible != this->mVisible;
	this->mVisible = p_isVisible;
	if(notify)
		this->notifyVisibilityChanged();
}

bool Sector::isVisited()
{
	return this->mVisited;
}

void Sector::setVisited( bool p_visited )
{
	this->mVisited = p_visited;
}

sf::Vector2i Sector::getAdjacentSectorId( int p_cardinality )
{
	switch(p_cardinality)
	{
	case CARDINALITY_NORTH:
		return this->getNorthSectorId();
		break;

	case CARDINALITY_NORTHEAST:
		return this->getNorthEastSectorId();
		break;

	case CARDINALITY_EAST:
		return this->getEastSectorId();
		break;

	case CARDINALITY_SOUTHEAST:
		return this->getSouthEastSectorId();
		break;

	case CARDINALITY_SOUTH:
		return this->getSouthSectorId();
		break;

	case CARDINALITY_SOUTHWEST:
		return this->getSouthWestSectorId();
		break;

	case CARDINALITY_WEST:
		return this->getWestSectorId();
		break;

	case CARDINALITY_NORTHWEST:
		return this->getNorthWestSectorId();
		break;

	default:
		return sf::Vector2i(0,0);
	}
}

sf::Vector2i Sector::getNorthSectorId()
{
	return sf::Vector2i(this->getIdSectorX(), this->getIdSectorY() - 1);
}

sf::Vector2i Sector::getNorthEastSectorId()
{
	return sf::Vector2i(this->getIdSectorX() + 1, this->getIdSectorY() - 1);
}

sf::Vector2i Sector::getEastSectorId()
{
	return sf::Vector2i(this->getIdSectorX() + 1, this->getIdSectorY());
}

sf::Vector2i Sector::getSouthEastSectorId()
{
	return sf::Vector2i(this->getIdSectorX() + 1, this->getIdSectorY() + 1);
}

sf::Vector2i Sector::getSouthSectorId()
{
	return sf::Vector2i(this->getIdSectorX(), this->getIdSectorY() + 1);
}

sf::Vector2i Sector::getSouthWestSectorId()
{
	return sf::Vector2i(this->getIdSectorX() - 1, this->getIdSectorY() + 1);
}

sf::Vector2i Sector::getWestSectorId()
{
	return sf::Vector2i(this->getIdSectorX() - 1, this->getIdSectorY());
}

sf::Vector2i Sector::getNorthWestSectorId()
{
	return sf::Vector2i(this->getIdSectorX() - 1, this->getIdSectorY() - 1);
}

int Sector::getObjectsCount()
{
	return this->mObjects.size();
}

MapObject* Sector::getObject( int p_index )
{
	return this->mObjects[p_index];
}

int Sector::getEntitiesCount()
{
	return this->mEntities.size();
}

Entity* Sector::getEntity( int p_index )
{
	return this->mEntities[p_index];
}

int Sector::getStarCount()
{
	return this->mStars.size();
}

Star* Sector::getStar( int p_index )
{
	return this->mStars[p_index];
}

std::vector<Planet*> Sector::getPlanets()
{
	std::vector<Planet*> planets;
	for(int i = 0; i < this->mObjects.size(); i++)
	{
		if(this->mObjects[i]->getObjectType() == MapObject::MapObjectType::TypePlanet)
			planets.push_back((Planet*)this->mObjects[i]);
	}
	return planets;
}

std::vector<CloudGaz*> Sector::getCloudGazs()
{
	std::vector<CloudGaz*> cloudGazs;
	for(int i = 0; i < this->mObjects.size(); i++)
	{
		if(this->mObjects[i]->getObjectType() == MapObject::MapObjectType::TypeCloudGaz)
			cloudGazs.push_back((CloudGaz*)this->mObjects[i]);
	}
	return cloudGazs;
}

std::vector<CloudWreck*> Sector::getCloudWrecks()
{
	std::vector<CloudWreck*> cloudWrecks;
	for(int i = 0; i < this->mObjects.size(); i++)
	{
		if(this->mObjects[i]->getObjectType() == MapObject::MapObjectType::TypeCloudWreck)
			cloudWrecks.push_back((CloudWreck*)this->mObjects[i]);
	}
	return cloudWrecks;
}

int Sector::getPlanetsCount()
{
	return this->mPlanetsCount;
}

void Sector::setPlanetsCount( int p_count )
{
	this->mPlanetsCount = p_count;
}

int Sector::getCloudGazsCount()
{
	return this->mCloudGazsCount;
}

void Sector::setCloudGazsCount( int p_count )
{
	this->mCloudGazsCount = p_count;
}

int Sector::getCloudWrecksCount()
{
	return this->mCloudWrecksCount;
}

void Sector::setCloudWrecksCount( int p_count )
{
	this->mCloudWrecksCount = p_count;
}

Sector::SectorColor Sector::getSectorColor()
{
	return this->mSectorColor;
}

void Sector::setSectorColor( SectorColor p_color )
{
	this->mSectorColor = p_color;
}

int Sector::getSectorColorSpread()
{
	return this->mSectorColorSpread;
}

void Sector::setSectorColorSpread( int p_spread )
{
	this->mSectorColorSpread = p_spread;
}

void Sector::decSectorColorSpread()
{
	this->mSectorColorSpread -= 1;
}


//*************************************************************
// Methode
//*************************************************************
sf::Vector2i Sector::convertPositionToId( sf::Vector2i p_position )
{
	return sf::Vector2i(p_position.x / SECTOR_WIDTH, p_position.y / SECTOR_HEIGHT);
}	

sf::Vector2i Sector::convertIdToPosition( sf::Vector2i p_id )
{
	return sf::Vector2i(p_id.x * SECTOR_WIDTH, p_id.y * SECTOR_HEIGHT);	
}

void Sector::calculateIdSector()
{
	this->mIdSector = Sector::convertPositionToId(sf::Vector2i(this->getX(), this->getY()));	
}

void Sector::calculatePosition()
{
	sf::Vector2i position = Sector::convertIdToPosition(this->mIdSector);
	this->mX = position.x;
	this->mY = position.y;
}

void Sector::update()
{
	// Sector need to be visible
	if(this->isVisible())
	{
		this->updateSpritePosition();
	}

	// Sector doesnt need to be visible
	this->updateMapObjects();
	this->updateEntities();
}

void Sector::update( sf::Event p_event )
{
	// Sector need to be visible
	if(this->isVisible())
	{

	}

	// Sector doesnt need to be visible
	this->updateMapObjects(p_event);
	this->updateEntities(p_event);
}

void Sector::updateSpritePosition()
{
	sf::Vector2f backgroundPosition;
	backgroundPosition.x = (float)this->getX() - Camera::camera->getPositionInPlane(SECTOR_PLANE).x;
	backgroundPosition.y = (float)this->getY() - Camera::camera->getPositionInPlane(SECTOR_PLANE).y;
	Camera::centerPosition(&backgroundPosition, SECTOR_PLANE);

	this->mBackgroundSprite.setPosition(backgroundPosition);
}

void Sector::draw()
{
	if(this->isVisible())
	{
		Resource::resource->getApp()->draw(this->mBackgroundSprite);		
	}	
}

bool Sector::contain( int p_x, int p_y )
{
	return	Tools::isBetween(p_x, this->getX(), this->getX() + SECTOR_WIDTH) &&
			Tools::isBetween(p_y, this->getY(), this->getY() + SECTOR_HEIGHT);
}

void Sector::addMapObject( MapObject* p_object, bool p_deleteIfMissPositioned )
{
	// Set sector
	p_object->setSector(this);

	// Set position
	int validateCount = 0;
	sf::Vector2i sectorPosition = this->getPosition();

	do 
	{
		double objectX = sectorPosition.x + Tools::random(0, SECTOR_WIDTH);
		double objectY = sectorPosition.y + Tools::random(0, SECTOR_HEIGHT);
		sf::Vector2f objectPosition(objectX, objectY);
		objectPosition = MapObject::convertPosition(objectPosition, MAPOBJECT_PLANE_21, p_object->getPlane());
		p_object->setPosition(objectPosition.x, objectPosition.y);
		validateCount++;
	} while (!this->validateMapObject(p_object) && validateCount < VALIDATECOUNT_MAX); 
	
	// Add
	if(validateCount >= VALIDATECOUNT_MAX && p_deleteIfMissPositioned)
	{
		delete p_object;
	}
	else
	{
		// Check if star
		if(ToolsMap::isStar(p_object))
			this->mStars.push_back((Star*)p_object);

		// Add mapObject
		std::vector<MapObject*>::iterator it = this->mObjects.begin();
		int insertPosition = 0;

		if(this->mObjects.size() > 0)
		{
			int currentIndex = 0;
			while(currentIndex < this->mObjects.size() && p_object->getPlane() <= this->mObjects[currentIndex]->getPlane())
			{
				currentIndex++;
				insertPosition++;
			}
		}

		if(insertPosition == this->mObjects.size() - 1)
			this->mObjects.push_back(p_object);
		else
			this->mObjects.insert(it + insertPosition, p_object);
	}
}	

void Sector::addEntity( Entity* p_entity )
{
	// Add to this
	p_entity->setSector(this);

	int validateCount = 0;
	sf::Vector2i sectorPosition = this->getPosition();

	do 
	{
		double objectX = sectorPosition.x + Tools::random(0, SECTOR_WIDTH);
		double objectY = sectorPosition.y + Tools::random(0, SECTOR_HEIGHT);
		sf::Vector2f objectPosition(objectX, objectY);
		objectPosition = MapObject::convertPosition(objectPosition, MAPOBJECT_PLANE_21, p_entity->getPlane());
		p_entity->setPosition(objectPosition.x, objectPosition.y);
		validateCount++;
	} while (!this->validateMapObject(p_entity) && validateCount < VALIDATECOUNT_MAX); 

	std::vector<Entity*>::iterator it = this->mEntities.begin();
	int insertPosition = 0;

	if(this->mEntities.size() > 0)
	{
		int currentIndex = 0;
		while(currentIndex < this->mEntities.size() && p_entity->getPlane() <= this->mEntities[currentIndex]->getPlane())
		{
			currentIndex++;
			insertPosition++;
		}
	}

	if(insertPosition == this->mEntities.size() - 1)
		this->mEntities.push_back(p_entity);
	else
		this->mEntities.insert(it + insertPosition, p_entity);

	// Add to others managers
	EntityManager::add(p_entity);
	Game::game->getMap()->getMapObjectSelector()->addMapObject(p_entity);
}

void Sector::removeEntity( Entity* p_entity )
{
	if(p_entity != NULL)
	{
		for(int i = 0; i < this->mEntities.size(); i++)
		{
			if(this->mEntities[i]->getId() == p_entity->getId())
				this->removeEntity(i);
		}
	}
}

void Sector::removeEntity( int p_index )
{
	// Remove from other managers
	Game::game->getMap()->getMapObjectSelector()->removeMapObject(this->mEntities[p_index]);
	EntityManager::remove(this->mEntities[p_index]->getId());

	// Remove from this
	this->mEntities.erase(this->mEntities.begin() + p_index);
}

bool Sector::validateMapObject( MapObject* p_object, bool p_checkAdj)
{
	std::vector<Sector*> listSector;
	Game::game->getMap()->getAdjacentSectors(this, listSector);
	listSector.push_back(this);

	for(int i = 0; i < listSector.size(); i++)
	{
		for(int j = 0; j < listSector[i]->getObjectsCount(); j++)
		{
			if(listSector[i]->getObject(j)->getPlane() == p_object->getPlane())
			{
				if(listSector[i]->getObject(j)->intersect(p_object))
					return false;
			}
		}
	}

	return true;
}

void Sector::updateMapObjects()
{
	for(int i = 0; i < this->mObjects.size(); i++)
	{
		this->mObjects[i]->update();	
	}
}

void Sector::updateEntities()
{
	for(int i = 0; i < this->mEntities.size(); i++)
	{
		this->mEntities[i]->update();	

		if(this->mEntities[i]->isDestroy())
			this->removeEntity(i);
	}
}

void Sector::updateMapObjects( sf::Event p_event )
{
	for(int i = 0; i < this->mObjects.size(); i++)
	{
		this->mObjects[i]->update(p_event);	
	}
}

void Sector::updateEntities( sf::Event p_event )
{
	for(int i = 0; i < this->mEntities.size(); i++)
	{
		this->mEntities[i]->update(p_event);	
	}
}

void Sector::drawMapObjects()
{
	for(int i = MapObject::getPlaneBackground(); i >= MapObject::getPlaneForeground(); i--)
	{
		this->drawMapObjects(i);
	}
}

void Sector::drawEntities()
{
	for(int i = MapObject::getPlaneBackground(); i >= MapObject::getPlaneForeground(); i--)
	{
		this->drawEntities(i);
	}
}

void Sector::drawMapObjects( int p_plane )
{
	for(int i = 0; i < this->mObjects.size(); i++)
	{
		if(this->mObjects[i]->getPlane() == p_plane)
			this->mObjects[i]->draw();
	}
}

void Sector::drawEntities( int p_plane )
{
	for(int i = 0; i < this->mEntities.size(); i++)
	{
		if(this->mEntities[i]->getPlane() == p_plane)
			this->mEntities[i]->draw();
	}
}

void Sector::notifyVisibilityChanged()
{
	for(int i = 0; i < this->mObjects.size(); i++)
	{
		this->mObjects[i]->setVisible(this->isVisible());
	}

	for(int i = 0; i < this->mEntities.size(); i++)
	{
		this->mEntities[i]->setVisible(this->isVisible());

		if(this->isVisible())
		{
			EntityManager::add(this->mEntities[i]);
			Game::game->getMap()->getMapObjectSelector()->addMapObject(this->mEntities[i]);
		}
		else
		{
			Game::game->getMap()->getMapObjectSelector()->removeMapObject(this->mEntities[i]);
			EntityManager::remove(this->mEntities[i]->getId(), false);
		}
	}
}

bool Sector::canSpreadSectorColor()
{
	return this->mSectorColorSpread > 0;
}






