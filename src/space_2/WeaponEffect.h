#pragma once
#include "EntityEffect.h"
#include "Clock.h"

class TurretEffect;

class WeaponEffect : public EntityEffect
{
public:
	// Constructor - Destructor
	WeaponEffect(Entity* p_entity, Json::Value p_weaponJson);
	WeaponEffect(TurretEffect* p_turret, float p_offsetx, float p_offsety);
	~WeaponEffect(void);

	// Getters - Setters
	float getOffsetAmmoX();
	float getOffsetAmmoY();

	bool isFiring();
	void setFiring(bool p_firing);

	// Methods
	void update();
	void updateWeapon();
	void updatePosition();
	void updateOffsetRotate();
	void updateFiring();
	void draw();


private:
	// Attributs
	TurretEffect* mTurret;
	sf::Sprite mWeaponSprite;
	sf::Sprite mWeaponFireSprite;
	bool mFiring;
	mks::Clock mFiringClock;
};

