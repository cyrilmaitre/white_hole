#pragma once
#include "Entity.h"
#include "NpcShip.h"
#include "Station.h"
#include "Containerable.h"

class WreckMini;

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
	Wreck(Entity* p_entity);
	void init();
	~Wreck(void);

	// Getters - Setters
	std::string getName();
	void setName(std::string p_name);

	long getCredit();
	void setCredit(long p_credit);

	bool isOutOfDate();

	// Methods
	void update();
	void update(sf::Event p_event);
	void updateWreckMini();
	void draw();
	void loadSprite();
	void loadFromNpc(Npc* p_npc);
	void loadFromEntity(Entity* p_entity);
	void loadFromNpcShip(NpcShip* p_npcShip);
	void loadFromStation(Station* p_station);

private:
	// Attributs
	std::string mName;
	long mCredit;

	std::vector<WreckMini*> mWreckMini;
};

