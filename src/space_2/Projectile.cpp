#include "Projectile.h"
#include "ToolsMap.h"
#include "AutoManager.h"
#include "ImpactManager.h"
#include "Weapon.h"


//*************************************************************
// Define
//*************************************************************
#define TARGET_DISTANCE_MAX		5
#define TARGET_HITBOX_OFFSET	0.1


//*************************************************************
// Constructor - Destructor
//*************************************************************
Projectile::Projectile( Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale, sf::Color p_color )
{
	this->mWeapon = p_weapon;
	this->mScale = 1;
	this->setScale(p_scale);
	this->setColor(p_color);

	this->setVelocityMax(p_weapon->getAmmo()->getVelocityMax());
	this->setQuickening(p_weapon->getAmmo()->getQuickening());
	this->setRotationVelocityInstant(true);

	WeaponEffect* weaponFire = p_source->getWeaponToFire();
	this->setX(p_source->Object::getX() + weaponFire->getOffsetAmmoX());
	this->setY(p_source->Object::getY() + weaponFire->getOffsetAmmoY());
	this->setSourceX(p_source->Object::getX());
	this->setSourceY(p_source->Object::getY());
	weaponFire->setFiring(true);

	int hitBoxWidth = (int)((float)p_target->getHitBox().width * TARGET_HITBOX_OFFSET);
	int hitBoxHeight = (int)((float)p_target->getHitBox().height * TARGET_HITBOX_OFFSET);
	this->setTargetOffsetX(p_source->getTargetOffsetX() + (Tools::random(0, hitBoxWidth) - (hitBoxWidth / 2)));
	this->setTargetOffsetY(p_source->getTargetOffsetY() + (Tools::random(0, hitBoxHeight) - (hitBoxHeight / 2)));

	this->getSource()->setEntity(p_source);
	this->getTarget()->setEntity(p_target);
	if(this->getTarget()->getEntity()->hasShield())
		this->setTargetDistanceMax(this->getTarget()->getEntity()->getRadius() / 2);
	else
		this->setTargetDistanceMax(TARGET_DISTANCE_MAX);
	this->setMode(MovableMode::ModeNormalWithoutDecelerate);

	this->EntityMovable::updateRotation();
	this->Rotable::updateRotation();
	this->update();
}

Projectile::~Projectile(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
EntityTarget* Projectile::getSource()
{
	return &this->mSource;
}

bool Projectile::isFinished()
{
	return	!this->getTarget()->isEntityValid() ||
			!this->getSource()->isEntityValid() ||
			this->mClockAuto.getElapsedTimeAsSeconds() > this->mWeapon->getAmmo()->getLifeTime() || 
			this->isTargetReached();
}

Weapon* Projectile::getWeapon()
{
	return this->mWeapon;
}

void Projectile::setWeapon( Weapon* p_weapon )
{
	this->mWeapon = p_weapon;
}

sf::Color Projectile::getColor()
{
	return this->mColor;
}

void Projectile::setColor( sf::Color p_color )
{
	if(this->mColor != p_color)
	{
		this->mColor = p_color;
		this->notifyColorChanged();
	}
}

Impact::ImpactType Projectile::getImpactType()
{
	return this->mImpactType;
}

void Projectile::setImpactType( Impact::ImpactType p_type )
{
	this->mImpactType = p_type;
}


//*************************************************************
// Methods
//*************************************************************
void Projectile::update()
{
	EntityMovable::update();
}

void Projectile::updatePosition()
{
	if(this->getTarget()->isEntityValid())
	{
		double newPositionX = this->Object::getX() + this->getMoveX();
		double newPositionY = this->Object::getY() + this->getMoveY();
		bool betweenX = Tools::isBetween(this->getTargetX(), this->Object::getX(), newPositionX);
		bool betweenY = Tools::isBetween(this->getTargetY(), this->Object::getY(), newPositionY);

		if(betweenX || betweenY)
		{
			if(betweenX)
				this->setX(this->getTargetX());
			else
				this->setX(newPositionX);

			if(betweenY)
				this->setY(this->getTargetY());
			else
				this->setY(newPositionY);
		}
		else
		{
			this->setX(newPositionX);
			this->setY(newPositionY);
		}
	}
}

void Projectile::draw()
{
	EntityMovable::draw();
}

void Projectile::notifyFinished()
{
	if(this->getTarget()->isEntityValid() && this->getSource()->isEntityValid() && this->isTargetReached())
	{
		if(this->getTarget()->getEntity()->hasShield())
		{
			this->getTarget()->getEntity()->shieldImpact();
		}
		else
		{
			AutoManager::add(ImpactManager::getImpact(this->getImpactType(), this->getTarget()->getEntity(), this->getTargetOffsetX(), this->getTargetOffsetY(), this->getScale()));
			this->playSoundImpact();
		}

		this->getTarget()->getEntity()->setAttacked(true);
		this->getTarget()->getEntity()->takeDamage(this->mWeapon);
	}
}

void Projectile::notifyScaleChanged()
{

}

void Projectile::notifyColorChanged()
{

}

void Projectile::playSoundImpact()
{

}


