#pragma once
#include "Projectile.h"


class ProjectileMissile : public Projectile
{
public:
	// Constructor - Destructor
	ProjectileMissile(Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale = 1, sf::Color p_color = sf::Color(255, 255, 255, 0));
	~ProjectileMissile(void);

	// Methods
	void loadSprite();
	void notifyScaleChanged();
	void notifyRotationChanged();
	void notifyColorChanged();
};

