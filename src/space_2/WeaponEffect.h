#pragma once
#include "EntityEffect.h"

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

	// Methods
	void update();
	void updateWeapon();
	void updatePosition();
	void updateOffsetRotate();
	void draw();


private:
	// Attributs
	TurretEffect* mTurret;
	sf::Sprite mWeaponSprite;
};

