#include "ProjectileBullet.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ProjectileBullet::ProjectileBullet(Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale, sf::Color p_color) : Projectile(p_source, p_target, p_weapon, p_scale, p_color)
{
	this->setImpactType(Impact::ImpactType::Bullet);
	this->setVisible(true);
	this->loadSprite();
}

ProjectileBullet::~ProjectileBullet(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void ProjectileBullet::loadSprite()
{
	Projectile::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_BULLET));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	this->mObjectSprite->setScale(this->getScale(), this->getScale());
	this->mObjectSprite->setRotation(this->getRotation());
	this->mObjectSprite->setColor(this->getColor());

	this->updateSprite();
}

void ProjectileBullet::notifyScaleChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setScale(this->getScale(), this->getScale());
}

void ProjectileBullet::notifyColorChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setColor(this->getColor());
}
