#include "ProjectileLaserBall.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ProjectileLaserBall::ProjectileLaserBall( Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale, sf::Color p_color ) : Projectile(p_source, p_target, p_weapon, p_scale, p_color)
{
	this->mSpriteLaserBall = NULL;

	this->setImpactType(Impact::ImpactType::Laser);
	this->setVisible(true);
	this->loadSprite();
}

ProjectileLaserBall::~ProjectileLaserBall(void)
{
	if(this->mSpriteLaserBall != NULL)
		delete this->mSpriteLaserBall;
}


//*************************************************************
// Methods
//*************************************************************
void ProjectileLaserBall::updateSprite()
{
	Projectile::updateSprite();

	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mSpriteLaserBall != NULL)
		this->mSpriteLaserBall->setPosition(objectPositionScreen.x, objectPositionScreen.y);
}

void ProjectileLaserBall::loadSprite()
{
	Projectile::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_LASERBALL_GLOW));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	this->mObjectSprite->setScale(this->getScale(), this->getScale());
	this->mObjectSprite->setRotation(this->getRotation());

	this->mSpriteLaserBall = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_LASERBALL));
	ToolsImage::setSpriteOriginCenter(this->mSpriteLaserBall);
	this->mSpriteLaserBall->setScale(this->getScale(), this->getScale());
	this->mSpriteLaserBall->setRotation(this->getRotation());
	this->mSpriteLaserBall->setColor(this->getColor());

	this->updateSprite();
}

void ProjectileLaserBall::unloadSprite()
{
	Projectile::unloadSprite();

	if(this->mSpriteLaserBall != NULL)
	{
		delete this->mSpriteLaserBall;
		this->mSpriteLaserBall = NULL;
	}
}

void ProjectileLaserBall::notifyScaleChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setScale(this->getScale(), this->getScale());
}

void ProjectileLaserBall::notifyColorChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setColor(this->getColor());
}

void ProjectileLaserBall::draw()
{
	Projectile::draw();
	if(this->mSpriteLaserBall != NULL)
		Resource::resource->getApp()->draw(*this->mSpriteLaserBall);
}
