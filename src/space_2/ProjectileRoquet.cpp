#include "ProjectileRoquet.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ProjectileRoquet::ProjectileRoquet( Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale, sf::Color p_color ) : Projectile(p_source, p_target, p_weapon, p_scale, p_color)
{
	this->setImpactType(Impact::ImpactType::Explosion);
	this->setVisible(true);
	this->loadSprite();
}

ProjectileRoquet::~ProjectileRoquet(void)
{

}


//*************************************************************
// Methods
//*************************************************************
void ProjectileRoquet::loadSprite()
{
	Projectile::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_ROCKET));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	this->mObjectSprite->setScale(this->getScale(), this->getScale());
	this->mObjectSprite->setRotation(this->getRotation());
	this->mObjectSprite->setColor(this->getColor());
}

void ProjectileRoquet::notifyScaleChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setScale(this->getScale(), this->getScale());
}

void ProjectileRoquet::notifyColorChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setColor(this->getColor());
}