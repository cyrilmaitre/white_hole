#pragma once
#include "Movable.h"
#include "EntityMovable.h"
#include "Auto.h"
#include "Impact.h"

class Weapon;

class Projectile : public EntityMovable, public Auto
{
public:
	// Enum
	enum ProjectileType
	{
		Bullet = 0,
		Laser,
		LaserBall,
		Missile,
		Roquet
	};

	// Constructor - Destructor
	Projectile(Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale = 1, sf::Color p_color = sf::Color(255, 255, 255, 0));
	~Projectile(void);

	// Getters - Setters
	EntityTarget* getSource();

	Weapon* getWeapon();
	void setWeapon(Weapon* p_weapon);

	sf::Color getColor();
	void setColor(sf::Color p_color);
	
	Impact::ImpactType getImpactType();
	void setImpactType(Impact::ImpactType p_type);

	bool isFinished();

	// Methods
	virtual void update();
	void updatePosition();
	virtual void draw();
	virtual void notifyFinished();
	virtual void notifyScaleChanged();
	virtual void notifyColorChanged();


private:
	// Attributs
	Weapon* mWeapon;
	EntityTarget mSource;

	sf::Color mColor;
	Impact::ImpactType mImpactType;
};

