#pragma once
#include "EntityEffect.h"
#include "Rotable.h"
#include "Clock.h"


class TurretEffect : public EntityEffect, public Rotable
{
public:
	// Constructor - Destructor
	TurretEffect(Entity* p_entity, Json::Value p_turretJson);
	~TurretEffect(void);

	// Getters - Setters

	// Methods
	void update();
	void updateTurret();
	void updatePosition();
	void draw();


private:
	// Attributs
	sf::Sprite mTurretSprite;
	float mTurretRotationTick;
	mks::Clock mTurretClock;

	// Methods
	void computeTurretRotationTick();
};

