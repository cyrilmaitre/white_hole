#include "ProjectileLaser.h"
#include "ToolsImage.h"
#include "ToolsMap.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ProjectileLaser::ProjectileLaser( Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale, sf::Color p_color ) : Projectile(p_source, p_target, p_weapon, p_scale, p_color)
{
	this->mSpriteLaser = NULL;

	this->setImpactType(Impact::ImpactType::Laser);
	this->setVisible(true);
	this->loadSprite();
}

ProjectileLaser::~ProjectileLaser(void)
{
	if(this->mSpriteLaser != NULL)
		delete this->mSpriteLaser;
}


//*************************************************************
// Methods
//*************************************************************
void ProjectileLaser::updateSprite()
{
	Projectile::updateSprite();

	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mSpriteLaser != NULL)
		this->mSpriteLaser->setPosition(objectPositionScreen.x, objectPositionScreen.y);
}

void ProjectileLaser::loadSprite()
{
	Projectile::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_LASER_GLOW));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	this->mObjectSprite->setScale(this->getScale(), this->getScale());
	this->mObjectSprite->setRotation(this->getRotation());

	this->mSpriteLaser = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_LASER));
	ToolsImage::setSpriteOriginCenter(this->mSpriteLaser);
	this->mSpriteLaser->setScale(this->getScale(), this->getScale());
	this->mSpriteLaser->setRotation(this->getRotation());
	this->mSpriteLaser->setColor(this->getColor());

	this->updateSprite();
}

void ProjectileLaser::unloadSprite()
{
	Projectile::unloadSprite();

	if(this->mSpriteLaser != NULL)
	{
		delete this->mSpriteLaser;
		this->mSpriteLaser = NULL;
	}
}

void ProjectileLaser::notifyScaleChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setScale(this->getScale(), this->getScale());

	if(this->mSpriteLaser != NULL)
		this->mSpriteLaser->setScale(this->getScale(), this->getScale());
}

void ProjectileLaser::notifyColorChanged()
{
	if(this->mSpriteLaser != NULL)
		this->mSpriteLaser->setColor(this->getColor());
}

void ProjectileLaser::notifyRotationChanged()
{
	Projectile::notifyRotationChanged();

	if(this->mSpriteLaser != NULL)
		this->mSpriteLaser->setRotation(this->getRotation());
}

void ProjectileLaser::draw()
{
	Projectile::draw();
	if(this->mSpriteLaser != NULL)
		Resource::resource->getApp()->draw(*this->mSpriteLaser);
}
