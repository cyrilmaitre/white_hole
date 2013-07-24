#pragma once
#include "Resource.h"
#include "Entity.h"


class EntityManager
{
public:
	// Getters - Setters
	static int getEntitiesCount();
	static Entity* getEntity(int p_id);
	static bool hasEntity(int p_id);

	// Methods
	static Entity* add(Entity* p_entity);
	static void remove(int p_id, bool p_delete = true);
	static void remove(Entity* p_entity, bool p_delete = true);


private:
	// Constructor - Destructor
	EntityManager(void);
	~EntityManager(void);
	
	// Attributs
	static std::map<int, Entity*> mEntities;
};

