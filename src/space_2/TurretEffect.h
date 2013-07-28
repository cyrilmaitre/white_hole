#pragma once
#include "EntityEffect.h"
#include "Rotable.h"
#include "Clock.h"
#include "TurretEffectModel.h"


class TurretEffect : public EntityEffect, public Rotable
{
public:
	// Constructor - Destructor
	TurretEffect(Entity* p_entity, Json::Value p_turretJson);
	~TurretEffect(void);

	// Getters - Setters
	TurretEffectModel* getTurretModel();
	void setTurretModel(TurretEffectModel* p_model);

	// Methods
	void update();
	void updateTurret();
	void updatePosition();
	void draw();
	void notifyTurretModelChanged();


private:
	// Attributs
	TurretEffectModel* mTurretModel;
	sf::Sprite mTurretSprite;
	float mTurretRotationTick;
	mks::Clock mTurretClock;

	// Methods
	void computeTurretRotationTick();
};

