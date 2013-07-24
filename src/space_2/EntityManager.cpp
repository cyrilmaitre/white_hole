#include "EntityManager.h"
#include "AutoManager.h"
#include "ExplosionEffect.h"


//*************************************************************
// Init static
//*************************************************************
std::map<int, Entity*> EntityManager::mEntities;


//*************************************************************
// Constructor - Destructor
//*************************************************************
EntityManager::EntityManager(void)
{
}

EntityManager::~EntityManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int EntityManager::getEntitiesCount()
{
	return EntityManager::mEntities.size();
}

Entity* EntityManager::getEntity( int p_id )
{
	std::map<int, Entity*>::iterator it;
	it = EntityManager::mEntities.find(p_id);

	if(it != EntityManager::mEntities.end())
	{
		return it->second;
	}

	return NULL;
}

bool EntityManager::hasEntity( int p_id )
{
	std::map<int, Entity*>::iterator it;
	it = EntityManager::mEntities.find(p_id);

	return it != EntityManager::mEntities.end();
}


//*************************************************************
// Methods
//*************************************************************
Entity* EntityManager::add( Entity* p_entity )
{
	// Check if key exist
	bool isKeyExist = false;
	std::map<int, Entity*>::iterator it;
	it = EntityManager::mEntities.find(p_entity->getId());

	if(it != EntityManager::mEntities.end())
		isKeyExist = true;

	// Set
	if(!isKeyExist)
		EntityManager::mEntities.insert(std::pair<int, Entity*>(p_entity->getId(), p_entity));

	return p_entity;
}

void EntityManager::remove( int p_id, bool p_delete )
{
	if(EntityManager::hasEntity(p_id))
	{
		if(p_delete)
		{
			Entity* deleteEntity = EntityManager::getEntity(p_id);
			if(deleteEntity->isDestroy())
				deleteEntity->destroy();
			delete deleteEntity;
		}
		EntityManager::mEntities.erase(p_id);
	}
}

void EntityManager::remove( Entity* p_entity, bool p_delete )
{
	EntityManager::remove(p_entity->getId(), p_delete);
}
