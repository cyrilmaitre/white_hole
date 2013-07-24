#pragma once
#include "Projectile.h"


class ProjectileLaserBall : public Projectile
{
public:
	// Constructor - Destructor
	ProjectileLaserBall(Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale = 1, sf::Color p_color = sf::Color(255, 255, 255, 0));
	~ProjectileLaserBall(void);

	// Methods
	void loadSprite();
	void notifyScaleChanged();
	void notifyRotationChanged();
	void notifyColorChanged();
};

