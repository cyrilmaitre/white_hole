#pragma once
#include "Projectile.h"


class ProjectileBullet : public Projectile
{
public:
	// Constructor - Destructor
	ProjectileBullet(Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale = 1, sf::Color p_color = sf::Color(255, 255, 255, 0));
	~ProjectileBullet(void);

	// Methods
	void loadSprite();
	void notifyScaleChanged();
	void notifyRotationChanged();
	void notifyColorChanged();
};

