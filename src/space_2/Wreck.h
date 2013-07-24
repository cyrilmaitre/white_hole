#pragma once
#include "Entity.h"
#include "NpcShip.h"
#include "Containerable.h"

// Define
#define WRECK_OUTOFTIME			3600	// Hour
#define WRECK_SHIELD			0
#define WRECK_ARMOR				0
#define WRECK_STRUCTURE			100
#define WRECK_OPEN_DISTANCE		250
#define WRECK_CARGOMAX			20

class Wreck : public Entity, public Containerable
{
public:
	// Constructor - Destructor
	Wreck(NpcShip* p_npcShip);
	void init();
	~Wreck(void);

	// Getters - Setters
	std::string getName();
	void setName(std::string p_name);

	long getCredit();
	void setCredit(long p_credit);

	bool isOutOfDate();

	// Methods
	void loadSprite();
	void loadFromNpc(Npc* p_npc);
	void loadFromNpcShip(NpcShip* p_npcShip);
	void loadFromEntity(Entity* p_entity);


private:
	// Attributs
	std::string mName;
	long mCredit;
};

