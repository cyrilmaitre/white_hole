#include "ProjectileManager.h"
#include "ProjectileBullet.h"
#include "ProjectileLaser.h"
#include "ProjectileLaserBall.h"
#include "ProjectileMissile.h"
#include "ProjectileRoquet.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ProjectileManager::ProjectileManager(void)
{
}

ProjectileManager::~ProjectileManager(void)
{
}


//*************************************************************
// Methods
//*************************************************************
Projectile* ProjectileManager::getProjectile( Entity* p_source, Entity* p_target, Weapon* p_weapon )
{
	AmmoModel* ammoModel = p_weapon->getAmmo();
	float projectileScale = ammoModel->getProjectileScale();
	sf::Color projectileColor = ToolsImage::hexaToColor(ammoModel->getProjectileColor());
	switch(ammoModel->getProjectileType())
	{
	case Projectile::ProjectileType::Bullet:
		return new ProjectileBullet(p_source, p_target, p_weapon, projectileScale, projectileColor);
		break;

	case Projectile::ProjectileType::Laser:
		return new ProjectileLaser(p_source, p_target, p_weapon, projectileScale, projectileColor);
		break;

	case Projectile::ProjectileType::LaserBall:
		return new ProjectileLaserBall(p_source, p_target, p_weapon, projectileScale, projectileColor);
		break;

	case Projectile::ProjectileType::Missile:
		return new ProjectileMissile(p_source, p_target, p_weapon, projectileScale, projectileColor);
		break;

	case Projectile::ProjectileType::Roquet:
		return new ProjectileRoquet(p_source, p_target, p_weapon, projectileScale, projectileColor);
		break;
	}
}
