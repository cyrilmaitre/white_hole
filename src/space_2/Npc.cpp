#include "Npc.h"
#include "Game.h"
#include "ToolsMap.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
#define UPDATEAGGRO_TICK		1 // Sec


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Npc::Npc( Entity* p_entity )
{
	this->mEntity = p_entity;
}

Npc::~Npc(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Entity* Npc::getEntity()
{
	return this->mEntity;
}

EntityTarget* Npc::getEntityBinded()
{
	return &this->mEntityBinded;
}

std::vector<Entity*> Npc::getEntityCanAggro()
{
	std::vector<Entity*> npcs;

	// From NpcShipSpawner
	for(int i = 0; i < Game::game->getMap()->getNpcShipSpawner()->getSpawnedNpcShipCount(); i++)
	{
		NpcShip* currentShip = Game::game->getMap()->getNpcShipSpawner()->getSpawnedNpcShip(i);
		if(this->getNpcType()->canAggro(currentShip->getNpcType()))
		{
			npcs.push_back(currentShip);
		}
	}

	// From Sectors
	Sector* currentSector = Game::game->getMap()->getCurrentSector();
	std::vector<Sector*> listSector;
	Game::game->getMap()->getAdjacentSectors(currentSector, listSector);
	listSector.push_back(currentSector);

	for(int i = 0; i < listSector.size(); i++)
	{
		for(int j = 0; j < listSector[i]->getEntitiesCount(); j++)
		{
			Entity* currentEntity = listSector[i]->getEntity(j);
			Npc* currentNpc = dynamic_cast<Npc*>(currentEntity);
			
			if(currentNpc != 0)
			{
				if(this->getNpcType()->canAggro(currentNpc->getNpcType()))
					npcs.push_back(currentEntity);
			}
		}
	}

	// Player
	if(this->getNpcType()->canAggro(Game::game->getShipPiloted()->getNpcType()))
		npcs.push_back(Game::game->getShipPiloted());

	return npcs;
}

std::vector<Entity*> Npc::getEntityCanAggroInRange()
{
	std::vector<Entity*> npcs = this->getEntityCanAggro();
	std::vector<Entity*> npcsInRange;

	for(int i = 0; i < npcs.size(); i++)
	{
		if(ToolsMap::getDistance(this->getEntity(), npcs[i]) <= this->getAggroRange())
			npcsInRange.push_back(npcs[i]);
	}

	return npcsInRange;
}

Entity* Npc::getEntityCanAggroInRangeWeaker()
{
	std::vector<Entity*> npcs = this->getEntityCanAggroInRange();

	if(npcs.size() > 0)
	{
		// Algo to get the weaker npc
		return npcs[0];
	}
	
	return NULL;
}


//*************************************************************
// Methods
//*************************************************************
void Npc::update()
{
	if(!this->getEntity()->getTarget()->isEntityValid())
	{
		if(this->mClockUpdateAggro.getElapsedTimeAsSeconds() > UPDATEAGGRO_TICK)
		{
			this->mClockUpdateAggro.restart();

			Entity* potentialTarget = this->getEntityCanAggroInRangeWeaker();
			if(potentialTarget != NULL)
				this->getEntity()->getTarget()->setEntity(potentialTarget);
		}
	}
	else
	{
		this->getEntity()->fire(this->getEntity()->getTarget()->getEntity(), this->getEntity());
	}
}

void Npc::loadNpcDataFromConfig( KeyValueFile *p_config )
{
	NpcData::loadNpcDataFromConfig(p_config);

	this->setLevel(this->generateLevel());
	this->loadWeaponsToEntity(this->getEntity());
}

void Npc::loadNpcDataFromNpcData( NpcData* p_object )
{
	NpcData::loadNpcDataFromNpcData(p_object);

	this->setLevel(this->generateLevel());
	this->loadWeaponsToEntity(this->getEntity());
}

void Npc::notifyNpcTypeChanged()
{
	this->getEntity()->notifyNpcTypeChanged(this->getNpcType());
}






