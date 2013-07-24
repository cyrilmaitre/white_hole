#pragma once
#include "Resource.h"
#include "NpcShip.h"
#include "Clock.h"


class NpcShipSpawner
{
public:
	// Constructor - Destructor
	NpcShipSpawner(void);
	~NpcShipSpawner(void);

	// Getters - Setters
	int getNpcShipCountByType(long p_idType);
	bool isOutOfRange(NpcShip* p_ship, double p_charShipX, double p_charShipY);

	int getSpawnedNpcShipCount();
	NpcShip* getSpawnedNpcShip(int p_index);

	// Methods
	void addNpcShip(NpcShip* p_ship);
	void removeNpcShip(NpcShip *p_ship);
	void removeNpcShip(long p_id);
	void removeNpcShip(int p_position);
	void update();
	void updateSpawn();
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	std::vector<NpcShip*> mSpawnedNpcShip;
	mks::Clock mSpawnClock;
};