#include "WeaponEffect.h"
#include "ToolsImage.h"
#include "TurretEffect.h"


//*************************************************************
// Define
//*************************************************************
#define JSON_SPRITE					"sprite"
#define SPRITE_DEFAULT				"radar_1.png"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
WeaponEffect::WeaponEffect( Entity* p_entity, Json::Value p_weaponJson ) : EntityEffect(p_entity, p_weaponJson)
{
	this->mTurret = NULL;
	this->mWeaponSprite.setTexture(*Resource::resource->getTexture(p_weaponJson.get(JSON_SPRITE, SPRITE_DEFAULT).asString()));
	ToolsImage::setSpriteOriginCenter(&this->mWeaponSprite);
	ToolsImage::resizeSprite(&this->mWeaponSprite, this->getSize(), this->getSize());
}

WeaponEffect::WeaponEffect( TurretEffect* p_turret, float p_offsetx, float p_offsety ) : EntityEffect(NULL, NULL)
{
	this->mTurret = p_turret;
	this->mWeaponSprite.setTexture(*Resource::resource->getTexture(this->mTurret->getWeaponEffectSprite()));
	ToolsImage::setSpriteOriginCenter(&this->mWeaponSprite);
	this->setSize(this->mWeaponSprite.getLocalBounds().width);

	this->setOffsetX(p_offsetx);
	this->setOffsetY(p_offsety - this->mWeaponSprite.getLocalBounds().height / 2);
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
	return this->getOffsetXRotate();
}

float WeaponEffect::getOffsetAmmoY()
{
	return this->getOffsetYRotate() + this->getEntity()->getRocking();
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
	}
}

void WeaponEffect::updateWeapon()
{
	if(this->mTurret != NULL)
		this->mWeaponSprite.setRotation(this->mTurret->getRotation() + this->mTurret->getEntity()->getRotation());
	else
		this->mWeaponSprite.setRotation(this->getEntity()->getRotation());
}

void WeaponEffect::updatePosition()
{
	if(this->mTurret != NULL)
		this->mWeaponSprite.setPosition(	this->mTurret->getEntity()->getScreenX() + this->mTurret->getOffsetXRotate() + this->getOffsetXRotate(), 
											this->mTurret->getEntity()->getScreenY() + this->mTurret->getEntity()->getRocking() + this->mTurret->getOffsetYRotate() + this->getOffsetYRotate());	
	else
		this->mWeaponSprite.setPosition(	this->getEntity()->getScreenX() + this->getOffsetXRotate(), 
											this->getEntity()->getScreenY() + this->getEntity()->getRocking() + this->getOffsetYRotate());	
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
	}
}

