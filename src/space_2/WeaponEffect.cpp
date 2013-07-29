#include "WeaponEffect.h"
#include "ToolsImage.h"
#include "TurretEffect.h"


//*************************************************************
// Define
//*************************************************************
#define JSON_SPRITE					"sprite"
#define SPRITE_DEFAULT				"radar_1.png"
#define SPRITE_FIRE					"cannon_fire_effect.png"
#define SPRITE_FIRE_PERCENT			0.75	// %
#define FIRING_TIME					150		// ms


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
WeaponEffect::WeaponEffect( Entity* p_entity, Json::Value p_weaponJson ) : EntityEffect(p_entity, p_weaponJson)
{
	this->mTurret = NULL;
	
	this->mWeaponSprite.setTexture(*Resource::resource->getTexture(p_weaponJson.get(JSON_SPRITE, SPRITE_DEFAULT).asString()));
	ToolsImage::setSpriteOriginCenter(&this->mWeaponSprite);
	ToolsImage::resizeSprite(&this->mWeaponSprite, this->getSize(), this->getSize());

	this->mWeaponFireSprite.setTexture(*Resource::resource->getTexture(SPRITE_FIRE));
	this->mWeaponFireSprite.setOrigin(this->mWeaponFireSprite.getLocalBounds().width / 2, this->mWeaponFireSprite.getLocalBounds().height);
	ToolsImage::resizeSprite(&this->mWeaponFireSprite, this->getSize() * SPRITE_FIRE_PERCENT, this->getSize() * SPRITE_FIRE_PERCENT);
}

WeaponEffect::WeaponEffect( TurretEffect* p_turret, float p_offsetx, float p_offsety ) : EntityEffect(NULL, NULL)
{
	this->mTurret = p_turret;
	this->mWeaponSprite.setTexture(*Resource::resource->getTexture(this->mTurret->getWeaponEffectSprite()));
	ToolsImage::setSpriteOriginCenter(&this->mWeaponSprite);
	this->mWeaponSprite.setScale(this->mTurret->getTurretScale(), this->mTurret->getTurretScale());
	this->setSize(this->mWeaponSprite.getGlobalBounds().width);

	this->mWeaponFireSprite.setTexture(*Resource::resource->getTexture(SPRITE_FIRE));
	this->mWeaponFireSprite.setOrigin(this->mWeaponFireSprite.getLocalBounds().width / 2, this->mWeaponFireSprite.getLocalBounds().height);
	ToolsImage::resizeSprite(&this->mWeaponFireSprite, this->getSize() * SPRITE_FIRE_PERCENT, this->getSize() * SPRITE_FIRE_PERCENT);

	this->setOffsetX(p_offsetx);
	this->setOffsetY(p_offsety - this->mWeaponSprite.getGlobalBounds().height / 2);
	this->updateOffsetRotate();
}

WeaponEffect::~WeaponEffect(void)
{
}


//*************************************************************
// Getters - Setterss
//*************************************************************
float WeaponEffect::getOffsetAmmoX()
{
	if(this->mTurret != NULL)
		return this->mTurret->getOffsetXRotate() + this->getOffsetXRotate();
	else
		return this->getOffsetXRotate();
}

float WeaponEffect::getOffsetAmmoY()
{
	if(this->mTurret != NULL)
		return this->mTurret->getEntity()->getRocking() + this->mTurret->getOffsetYRotate() + this->getOffsetYRotate();
	else
		return this->getOffsetYRotate() + this->getEntity()->getRocking();
}

bool WeaponEffect::isFiring()
{
	bool returnValue = this->mFiring;
	this->mFiring = false;
	return returnValue;
}

void WeaponEffect::setFiring( bool p_firing )
{
	this->mFiring = p_firing;
}


//*************************************************************
// Methods
//*************************************************************
void WeaponEffect::update()
{
	EntityEffect::update();
	if((this->mTurret != NULL && this->mTurret->getEntity()->isVisible()) || (this->getEntity() != NULL && this->getEntity()->isVisible()))
	{
		this->updateWeapon();
		this->updatePosition();
		this->updateFiring();
	}
}

void WeaponEffect::updateFiring()
{
	if(this->isFiring())
		this->mFiringClock.restart();

	if(this->mFiringClock.getElapsedTimeAsMilliseconds() < FIRING_TIME)
		this->mWeaponFireSprite.setColor(sf::Color(255, 255, 255, 255 * (1.f - (float)this->mFiringClock.getElapsedTimeAsMilliseconds() / (float)FIRING_TIME)));
	else
		this->mWeaponFireSprite.setColor(sf::Color(255, 255, 255, 0));
}

void WeaponEffect::updateWeapon()
{
	if(this->mTurret != NULL)
	{
		float rotation = this->mTurret->getRotation() + this->mTurret->getEntity()->getRotation();
		this->mWeaponSprite.setRotation(rotation);
		this->mWeaponFireSprite.setRotation(rotation);
	}
	else
	{
		float rotation = this->getEntity()->getRotation();
		this->mWeaponSprite.setRotation(rotation);
		this->mWeaponFireSprite.setRotation(rotation);
	}
}

void WeaponEffect::updatePosition()
{
	if(this->mTurret != NULL)
	{
		float positionX = this->mTurret->getEntity()->getScreenX() + this->mTurret->getOffsetXRotate() + this->getOffsetXRotate();
		float positionY = this->mTurret->getEntity()->getScreenY() + this->mTurret->getEntity()->getRocking() + this->mTurret->getOffsetYRotate() + this->getOffsetYRotate();
		this->mWeaponSprite.setPosition(positionX, positionY);	
		this->mWeaponFireSprite.setPosition(positionX, positionY);
	}
	else
	{
		float positionX = this->getEntity()->getScreenX() + this->getOffsetXRotate();
		float positionY = this->getEntity()->getScreenY() + this->getEntity()->getRocking() + this->getOffsetYRotate();
		this->mWeaponSprite.setPosition(positionX, positionY);	
		this->mWeaponFireSprite.setPosition(positionX, positionY);
	}
}

void WeaponEffect::updateOffsetRotate()
{
	if(this->mTurret != NULL)
		this->mOffsetRotate = Tools::rotatePoint(this->mOffset, this->mTurret->getRotation() + this->mTurret->getEntity()->getRotation());
	else
		EntityEffect::updateOffsetRotate();
}

void WeaponEffect::draw()
{
	EntityEffect::draw();
	if((this->mTurret != NULL && this->mTurret->getEntity()->isVisible()) || (this->getEntity() != NULL && this->getEntity()->isVisible()))
	{
		Resource::resource->getApp()->draw(this->mWeaponSprite);
		Resource::resource->getApp()->draw(this->mWeaponFireSprite);
	}
}


