#include "ImpactManager.h"
#include "ImpactBullet.h"
#include "ImpactExplosion.h"
#include "ImpactLaser.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ImpactManager::ImpactManager(void)
{
}

ImpactManager::~ImpactManager(void)
{
}


//*************************************************************
// Methods
//*************************************************************
Impact* ImpactManager::getImpact( Impact::ImpactType p_type, Entity* p_target, float p_scale )
{
	switch(p_type)
	{
	case Impact::ImpactType::Bullet:
		return new ImpactBullet(p_target, p_scale);
		break;

	case Impact::ImpactType::Laser:
		return new ImpactLaser(p_target, p_scale);
		break;

	case Impact::ImpactType::Explosion:
		return new ImpactExplosion(p_target, p_scale);
		break;
	}
}
