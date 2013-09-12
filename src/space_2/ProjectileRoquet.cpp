#include "ProjectileRoquet.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ProjectileRoquet::ProjectileRoquet( Entity* p_source, Entity* p_target, Weapon* p_weapon, float p_scale, sf::Color p_color ) : Projectile(p_source, p_target, p_weapon, p_scale, p_color)
{
	this->mSpriteRoquetGlow = NULL;

	this->addReactorEffect(new ReactorEffect(this, 0 * this->getScale(), 32 * this->getScale(), 20 * this->getScale(), 0, 300));
	this->setImpactType(Impact::ImpactType::Explosion);
	this->setVisible(true);
	this->loadSprite();
}

ProjectileRoquet::~ProjectileRoquet(void)
{
	if(this->mSpriteRoquetGlow != NULL)
		delete this->mSpriteRoquetGlow;
}


//*************************************************************
// Methods
//*************************************************************
void ProjectileRoquet::updateSprite()
{
	Projectile::updateSprite();

	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mSpriteRoquetGlow != NULL)
		this->mSpriteRoquetGlow->setPosition(objectPositionScreen.x, objectPositionScreen.y);
}

void ProjectileRoquet::loadSprite()
{
	Projectile::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_ROCKET));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	this->mObjectSprite->setScale(this->getScale(), this->getScale());
	this->mObjectSprite->setRotation(this->getRotation());
	
	this->mSpriteRoquetGlow = new sf::Sprite(*Resource::resource->getTexture(IMG_PROJECTILE_ROCKET_GLOW));
	ToolsImage::setSpriteOriginCenter(this->mSpriteRoquetGlow);
	this->mSpriteRoquetGlow->setScale(this->getScale(), this->getScale());
	this->mSpriteRoquetGlow->setRotation(this->getRotation());
	this->mSpriteRoquetGlow->setColor(this->getColor());

	this->updateSprite();
}

void ProjectileRoquet::unloadSprite()
{
	Projectile::unloadSprite();

	if(this->mSpriteRoquetGlow != NULL)
	{
		delete this->mSpriteRoquetGlow;
		this->mSpriteRoquetGlow = NULL;
	}
}

void ProjectileRoquet::notifyScaleChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setScale(this->getScale(), this->getScale());

	if(this->mSpriteRoquetGlow != NULL)
		this->mSpriteRoquetGlow->setScale(this->getScale(), this->getScale());
}

void ProjectileRoquet::notifyColorChanged()
{
	if(this->mSpriteRoquetGlow != NULL)
		this->mSpriteRoquetGlow->setColor(this->getColor());
}

void ProjectileRoquet::notifyRotationChanged()
{
	Projectile::notifyRotationChanged();

	if(this->mSpriteRoquetGlow != NULL)
		this->mSpriteRoquetGlow->setRotation(this->getRotation());
}

void ProjectileRoquet::draw()
{
	Projectile::draw();
	if(this->mSpriteRoquetGlow != NULL)
		Resource::resource->getApp()->draw(*this->mSpriteRoquetGlow);
}
