#include "ProjectileLaserBall.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ProjectileLaserBall::ProjectileLaserBall( Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale, sf::Color p_color ) : Projectile(p_source, p_target, p_weapon, p_scale, p_color)
{
	this->setImpactType(Impact::ImpactType::Laser);
	this->setVisible(true);
	this->loadSprite();
}

ProjectileLaserBall::~ProjectileLaserBall(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void ProjectileLaserBall::loadSprite()
{
	Projectile::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_LASERBALL));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	this->mObjectSprite->setScale(this->getScale(), this->getScale());
	this->mObjectSprite->setRotation(this->getRotation());
	this->mObjectSprite->setColor(this->getColor());
}

void ProjectileLaserBall::notifyScaleChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setScale(this->getScale(), this->getScale());
}

void ProjectileLaserBall::notifyRotationChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setRotation(this->getRotation());
}

void ProjectileLaserBall::notifyColorChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setColor(this->getColor());
}
