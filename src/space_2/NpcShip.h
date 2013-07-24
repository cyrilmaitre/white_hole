#pragma once
#include "NpcShipModel.h"
#include "Ship.h"
#include "NpcMovable.h"


class NpcShip: public Ship, public NpcMovable
{
public:
	// Constructor - Destructor
	NpcShip(double p_spawnX = 0, double p_spawnY = 0);
	~NpcShip(void);

	// Getters - Setters
	double getSpawnX();
	void setSpawnX(double p_spawnX);

	double getSpawnY();
	void setSpawnY(double p_spawnY);

	NpcShipModel *getNpcShipModel();
	void setNpcShipModel(NpcShipModel *p_model);

	// Methods
	void draw();
	void update();
	void update(sf::Event p_event);
	void loadFromNpcShipModel();
	void destroy();


private:
	// Attributs
	double mSpawnX;
	double mSpawnY;
	NpcShipModel *mNpcShipModel;
};

