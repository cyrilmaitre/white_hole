#pragma once
#include "Projectile.h"


class ProjectileLaser : public Projectile
{
public:
	// Constructor - Destructor
	ProjectileLaser(Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale = 1, sf::Color p_color = sf::Color(255, 255, 255, 0));
	~ProjectileLaser(void);

	// Methods
	void updateSprite();
	void loadSprite();
	void unloadSprite();
	void notifyScaleChanged();
	void notifyColorChanged();
	void notifyRotationChanged();
	void draw();


private:
	// Attributs
	sf::Sprite* mSpriteLaser;
};

