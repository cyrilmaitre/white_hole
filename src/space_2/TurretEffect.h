#pragma once
#include "EntityEffect.h"
#include "Rotable.h"
#include "Clock.h"
#include "TurretEffectModel.h"
#include "WeaponEffect.h"


class TurretEffect : public EntityEffect, public Rotable
{
public:
	// Constructor - Destructor
	TurretEffect(Entity* p_entity, Json::Value p_turretJson);
	~TurretEffect(void);

	// Getters - Setters
	TurretEffectModel* getTurretModel();
	void setTurretModel(TurretEffectModel* p_model);

	std::string getWeaponEffectSprite();
	void setWeaponEffectSprite(std::string p_sprite);

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

	std::string mWeaponEffectSprite;
	std::vector<WeaponEffect*> mWeaponEffect;

	// Methods
	void computeTurretRotationTick();
};

