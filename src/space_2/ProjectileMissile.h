#pragma once
#include "Projectile.h"


class ProjectileMissile : public Projectile
{
public:
	// Constructor - Destructor
	ProjectileMissile(Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale = 1, sf::Color p_color = sf::Color(255, 255, 255, 0));
	~ProjectileMissile(void);

	// Methods
	void updateSprite();
	void loadSprite();
	void unloadSprite();
	void notifyScaleChanged();
	void notifyColorChanged();
	void notifyRotationChanged();
	void draw();
	void playSoundImpact();


private:
	// Attributs
	sf::Sprite* mSpriteMissileGlow;
};

