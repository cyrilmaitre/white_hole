#include "ProjectileMissile.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ProjectileMissile::ProjectileMissile( Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale, sf::Color p_color) : Projectile(p_source, p_target, p_weapon, p_scale, p_color)
{
	this->mSpriteMissileGlow = NULL;

	// Configure reactor
	Json::Value jsonReactor;
	jsonReactor["x"] = 0;
	jsonReactor["y"] = 32;
	jsonReactor["type"] = 0;
	jsonReactor["size"] = 20;
	jsonReactor["reactoralphaspeed"] = 300;
	this->addReactorEffect(new ReactorEffect(this, jsonReactor));

	this->setImpactType(Impact::ImpactType::Explosion);
	this->setVisible(true);
	this->loadSprite();
}

ProjectileMissile::~ProjectileMissile(void)
{
	if(this->mSpriteMissileGlow != NULL)
		delete this->mSpriteMissileGlow;
}


//*************************************************************
// Methods
//*************************************************************
void ProjectileMissile::updateSprite()
{
	Projectile::updateSprite();

	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mSpriteMissileGlow != NULL)
		this->mSpriteMissileGlow->setPosition(objectPositionScreen.x, objectPositionScreen.y);
}

void ProjectileMissile::loadSprite()
{
	Projectile::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_MISSILE));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	this->mObjectSprite->setScale(this->getScale(), this->getScale());
	this->mObjectSprite->setRotation(this->getRotation());

	this->mSpriteMissileGlow = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_MISSILE_GLOW));
	ToolsImage::setSpriteOriginCenter(this->mSpriteMissileGlow);
	this->mSpriteMissileGlow->setScale(this->getScale(), this->getScale());
	this->mSpriteMissileGlow->setRotation(this->getRotation());
	this->mSpriteMissileGlow->setColor(this->getColor());

	this->updateSprite();
}

void ProjectileMissile::unloadSprite()
{
	Projectile::unloadSprite();

	if(this->mSpriteMissileGlow != NULL)
	{
		delete this->mSpriteMissileGlow;
		this->mSpriteMissileGlow = NULL;
	}
}

void ProjectileMissile::notifyScaleChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setScale(this->getScale(), this->getScale());

	if(this->mSpriteMissileGlow != NULL)
		this->mSpriteMissileGlow->setScale(this->getScale(), this->getScale());
}

void ProjectileMissile::notifyColorChanged()
{
	if(this->mSpriteMissileGlow != NULL)
		this->mSpriteMissileGlow->setColor(this->getColor());
}

void ProjectileMissile::notifyRotationChanged()
{
	Projectile::notifyRotationChanged();

	if(this->mSpriteMissileGlow != NULL)
		this->mSpriteMissileGlow->setRotation(this->getRotation());
}

void ProjectileMissile::draw()
{
	Projectile::draw();
	if(this->mSpriteMissileGlow != NULL)
		Resource::resource->getApp()->draw(*this->mSpriteMissileGlow);
}
