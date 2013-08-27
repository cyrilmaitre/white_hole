#pragma once
#include "NpcData.h"
#include "Entity.h"
#include "Levelable.h"
#include "MapObject.h"
#include "EntityTarget.h"

class Npc : public NpcData, public Levelable
{
public:
	// Constructor - Destructor
	Npc(Entity* p_entity);
	~Npc(void);

	// Getters - Setters
	Entity* getEntity();
	EntityTarget* getEntityBinded();

	std::vector<Entity*> getEntityCanAggro();
	std::vector<Entity*> getEntityCanAggroInRange();
	Entity* getEntityCanAggroInRangeWeaker();

	// Methods
	void update();
	void notifyNpcTypeChanged();
	void loadNpcDataFromConfig(KeyValueFile *p_config);
	void loadNpcDataFromNpcData(NpcData* p_object);


private:
	// Attributs
	Entity* mEntity;
	EntityTarget mEntityBinded;
	mks::Clock mClockUpdateAggro;
};

