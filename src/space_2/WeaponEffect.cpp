#include "WeaponEffect.h"
#include "ToolsImage.h"


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
	this->mWeaponSprite.setTexture(*Resource::resource->getTexture(p_weaponJson.get(JSON_SPRITE, SPRITE_DEFAULT).asString()));
	ToolsImage::setSpriteOriginCenter(&this->mWeaponSprite);
	ToolsImage::resizeSprite(&this->mWeaponSprite, this->getSize(), this->getSize());
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
	if(this->getEntity()->isVisible())
	{
		this->updateWeapon();
		this->updatePosition();
	}
}

void WeaponEffect::updateWeapon()
{
	this->mWeaponSprite.setRotation(this->getEntity()->getRotation());
}

void WeaponEffect::updatePosition()
{
	this->mWeaponSprite.setPosition(	this->getEntity()->getScreenX() + this->getOffsetXRotate(), 
									this->getEntity()->getScreenY() + this->getEntity()->getRocking() + this->getOffsetYRotate());	
}

void WeaponEffect::draw()
{
	EntityEffect::draw();
	if(this->getEntity()->isVisible())
	{
		Resource::resource->getApp()->draw(this->mWeaponSprite);
	}
}

