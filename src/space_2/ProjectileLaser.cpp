#include "ProjectileLaser.h"
#include "ToolsImage.h"
#include "ToolsMap.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ProjectileLaser::ProjectileLaser( Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale, sf::Color p_color ) : Projectile(p_source, p_target, p_weapon, p_scale, p_color)
{
	this->setImpactType(Impact::ImpactType::Laser);
	this->setVisible(true);
	this->loadSprite();
}

ProjectileLaser::~ProjectileLaser(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void ProjectileLaser::loadSprite()
{
	Projectile::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_LASER));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	this->mObjectSprite->setScale(this->getScale(), this->getScale());
	this->mObjectSprite->setRotation(this->getRotation());
	this->mObjectSprite->setColor(this->getColor());
}

void ProjectileLaser::notifyScaleChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setScale(this->getScale(), this->getScale());
}

void ProjectileLaser::notifyRotationChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setRotation(this->getRotation());
}

void ProjectileLaser::notifyColorChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setColor(this->getColor());
}
