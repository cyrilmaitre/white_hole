#include "NpcShipSpawner.h"
#include "Sector.h"
#include "Game.h"
#include "AutoManager.h"
#include "ExplosionEffect.h"
#include "EntityManager.h"


//*************************************************************
// Define
//*************************************************************
#define NPCSHIPSPAWNER_TICK				1	// In sec
#define NPCSHIPSPAWNER_SPAWN_DIST		15000


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
NpcShipSpawner::NpcShipSpawner(void)
{
}

NpcShipSpawner::~NpcShipSpawner(void)
{
	// Clear npcship
	for(int i = 0; i < this->mSpawnedNpcShip.size(); i++)
	{
		delete this->mSpawnedNpcShip[i];
	}
	this->mSpawnedNpcShip.clear();
}


//*************************************************************
// Getters - Setters
//*************************************************************
int NpcShipSpawner::getNpcShipCountByType(long p_idType)
{
	int count = 0;
	for(int i = 0; i < this->mSpawnedNpcShip.size(); i++)
	{
		if(this->mSpawnedNpcShip[i]->getNpcType()->getIdNpcType() == p_idType)
			count++;
	}
	return count;
}

bool NpcShipSpawner::isOutOfRange( NpcShip* p_ship, double p_charShipX, double p_charShipY )
{
	double shipX = p_ship->getX(SHIP_PLANE);
	double shipY = p_ship->getY(SHIP_PLANE);

	return  shipX < p_charShipX - NPCSHIPSPAWNER_SPAWN_DIST || 
			shipX > p_charShipX + NPCSHIPSPAWNER_SPAWN_DIST ||
			shipY < p_charShipY - NPCSHIPSPAWNER_SPAWN_DIST ||
			shipY > p_charShipY + NPCSHIPSPAWNER_SPAWN_DIST;
}

int NpcShipSpawner::getSpawnedNpcShipCount()
{
	return this->mSpawnedNpcShip.size();
}

NpcShip* NpcShipSpawner::getSpawnedNpcShip( int p_index )
{
	return this->mSpawnedNpcShip[p_index];
}


//*************************************************************
// Methods
//*************************************************************
void NpcShipSpawner::update()
{
	this->updateSpawn();
	for(int i = 0; i < this->mSpawnedNpcShip.size(); i++)
	{
		this->mSpawnedNpcShip[i]->update();

		// Dead
		if(this->mSpawnedNpcShip[i]->isDestroy())
		{
			this->removeNpcShip(this->mSpawnedNpcShip[i]);
			i--;	// Stay on the same index
		}
	}
}

void NpcShipSpawner::updateSpawn()
{
	CharacterShip* caracterShip = Game::game->getCharacter()->getShipPiloted();
	double characterShipX = caracterShip->getX(SHIP_PLANE);
	double characterShipY = caracterShip->getY(SHIP_PLANE);

	// Check out of range
	for(int i = 0; i < this->mSpawnedNpcShip.size(); i++)
	{
		if(this->isOutOfRange(this->mSpawnedNpcShip[i], characterShipX, characterShipY))
			this->removeNpcShip(this->mSpawnedNpcShip[i]);
	}

	// Spawn if max spawned not reached
	if(this->mSpawnClock.getElapsedTimeAsSeconds() > NPCSHIPSPAWNER_TICK)
	{
		Sector* currentSector = Game::game->getMap()->getCurrentSector();
		for(int i = 0; i < currentSector->getDangerLevel()->getShipTypeSpawnCount(); i++)
		{
			int npcShipTypeCurrent = currentSector->getDangerLevel()->getShipTypeSpawn(i);
			int npcShipTypeNumberCurrent = this->getNpcShipCountByType(npcShipTypeCurrent);
			int npcShipTypeNumberMax = currentSector->getDangerLevel()->getShipTypeSpawnNumber(npcShipTypeCurrent);
			if( npcShipTypeNumberCurrent < npcShipTypeNumberMax)
			{
				float random = ((float)Tools::random(0, 100)) / 100.f;
				std::map<NpcShipModel*, float> shipModelChance;
				currentSector->getDangerLevel()->getShipModelSpawnChanceByShipType(shipModelChance, npcShipTypeCurrent);
				std::vector<NpcShipModel*> shipModelSelected;

				for(std::map<NpcShipModel*, float>::iterator iter = shipModelChance.begin(); iter != shipModelChance.end(); ++iter)
				{
					if(iter->second >= random)
						shipModelSelected.push_back(iter->first);
				}

				std::random_shuffle(shipModelSelected.begin(), shipModelSelected.end());
				for(int i = 0; i < shipModelSelected.size(); i++)
				{
					if( npcShipTypeNumberCurrent < npcShipTypeNumberMax )
					{
						NpcShip *newNpcShip = new NpcShip();
						newNpcShip->setNpcShipModel(shipModelSelected[i]);
						newNpcShip->setSpawnX(Tools::random(-NPCSHIPSPAWNER_SPAWN_DIST, NPCSHIPSPAWNER_SPAWN_DIST) + characterShipX);
						newNpcShip->setSpawnY(Tools::random(-NPCSHIPSPAWNER_SPAWN_DIST, NPCSHIPSPAWNER_SPAWN_DIST) + characterShipY);
						this->addNpcShip(newNpcShip);

						npcShipTypeNumberCurrent++;
					}
				}
			}
		}

		// Restart tick
		this->mSpawnClock.restart();
	}
}

void NpcShipSpawner::update(sf::Event p_event)
{
	for(int i = 0; i < this->mSpawnedNpcShip.size(); i++)
	{
		this->mSpawnedNpcShip[i]->update(p_event);
	}
}

void NpcShipSpawner::draw()
{
	for(int i = 0; i < this->mSpawnedNpcShip.size(); i++)
	{
		this->mSpawnedNpcShip[i]->draw();
	}
}

void NpcShipSpawner::addNpcShip( NpcShip* p_ship )
{
	EntityManager::add(p_ship);
	Game::game->getMap()->getMapObjectSelector()->addMapObject(p_ship);
	this->mSpawnedNpcShip.push_back(p_ship);
}

void NpcShipSpawner::removeNpcShip( NpcShip *p_ship )
{
	this->removeNpcShip(p_ship->getIdMapObject());
}

void NpcShipSpawner::removeNpcShip( long p_id )
{
	for(int i = 0; i < this->mSpawnedNpcShip.size(); i++)
	{
		if(this->mSpawnedNpcShip[i]->getIdMapObject() == p_id)
		{
			this->removeNpcShip(i);
			break;
		}
	}	
}

void NpcShipSpawner::removeNpcShip( int p_position )
{
	Game::game->getMap()->getMapObjectSelector()->removeMapObject(this->mSpawnedNpcShip[p_position]);
	EntityManager::remove(this->mSpawnedNpcShip[p_position]);
	this->mSpawnedNpcShip.erase(this->mSpawnedNpcShip.begin() + p_position);
}

