#include "ProjectileMissile.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ProjectileMissile::ProjectileMissile( Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale, sf::Color p_color) : Projectile(p_source, p_target, p_weapon, p_scale, p_color)
{
	this->setImpactType(Impact::ImpactType::Explosion);
	this->setVisible(true);
	this->loadSprite();
}

ProjectileMissile::~ProjectileMissile(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void ProjectileMissile::loadSprite()
{
	Projectile::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_MISSILE));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	this->mObjectSprite->setScale(this->getScale(), this->getScale());
	this->mObjectSprite->setRotation(this->getRotation());
	this->mObjectSprite->setColor(this->getColor());
}

void ProjectileMissile::notifyScaleChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setScale(this->getScale(), this->getScale());
}

void ProjectileMissile::notifyRotationChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setRotation(this->getRotation());
}

void ProjectileMissile::notifyColorChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setColor(this->getColor());
}