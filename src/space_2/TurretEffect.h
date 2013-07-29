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

	float getTurretScale();
	void setTurretScale(float p_scale);

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
	std::string mWeaponEffectSprite;
	float mTurretScale;

	float mTurretRotationTick;
	mks::Clock mTurretClock;

	// Methods
	void computeTurretRotationTick();
};

