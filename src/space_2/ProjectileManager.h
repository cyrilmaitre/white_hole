#pragma once
#include "Projectile.h"
#include "Weapon.h"
#include "Entity.h"


class ProjectileManager
{
public:
	// Methods
	static Projectile* getProjectile(Entity* p_source, Entity* p_target, Weapon* p_weapon);


private:
	// Constructor - Destructor
	ProjectileManager(void);
	~ProjectileManager(void);
};

