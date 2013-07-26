#pragma once
#include "EntityEffect.h"

class WeaponEffect : public EntityEffect
{
public:
	// Constructor - Destructor
	WeaponEffect(Entity* p_entity, Json::Value p_weaponJson);
	~WeaponEffect(void);

	// Getters - Setters
	float getOffsetAmmoX();
	float getOffsetAmmoY();

	// Methods
	void update();
	void updateWeapon();
	void updatePosition();
	void draw();


private:
	// Attributs
	sf::Sprite mWeaponSprite;
};

