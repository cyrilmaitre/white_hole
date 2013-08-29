#pragma once
#include "Destructable.h"
#include "Movable.h"
#include "ShipModel.h"
#include "Containerable.h"
#include "EntityMovable.h"
#include "Clock.h"

// Define
#define SHIP_PLANE							MAPOBJECT_PLANE_1
#define SHIP_SPRITE_COLUMN					32
#define SHIP_SPRITE_LINE					5
#define SHIP_FIRING_FREQUENCY				100
#define SHIP_FIRING_COUNT					4
#define SHIP_FIRING_CYCLE					SHIP_FIRING_FREQUENCY * SHIP_FIRING_COUNT

class Ship: public EntityMovable
{
public:
	// Constructeur - Destructeur
	Ship(double p_x = 0, double p_y = 0);
	~Ship(void);

	// Getters - Setters
	ShipModel *getShipModel();
	void setShipModel(ShipModel *p_shipModel);

	// Method
	void draw();
	void update();
	void update(sf::Event p_event);
	void loadSprite();
	virtual void loadFromShipModel();


protected:
	// Attributs
	ShipModel *mShipModel;
	mks::Clock mClockFiring;
};

