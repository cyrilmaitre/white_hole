#include "TurretEffect.h"
#include "Tools.h"
#include "ToolsImage.h"
#include "ToolsMap.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define JSON_ROTATIONVELOCITY		"rotationvelocity"
#define JSON_TURRETMODEL			"turret_model"
#define JSON_WEAPONSPRITE			"weapon_sprite"
#define WEAPONSPRITE_DEFAULT		"cannon_basic.png"
#define SPRITE_DEFAULT				"turret_one_1.png"
#define TURRET_ROTATION_TICKMIN		3.f	// sec
#define TURRET_ROTATION_TICKMAX		6.f // sec


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
TurretEffect::TurretEffect( Entity* p_entity, Json::Value p_turretJson ) : EntityEffect(p_entity, p_turretJson)
{
	this->setRotationVelocity(p_turretJson.get(JSON_ROTATIONVELOCITY, 0).asFloat());
	this->setWeaponEffectSprite(p_turretJson.get(JSON_WEAPONSPRITE, WEAPONSPRITE_DEFAULT).asString());

	this->mTurretModel = FactoryGet::getTurretEffectModelFactory()->getTurretEffectModel(p_turretJson.get(JSON_TURRETMODEL, 1).asInt());
	this->mTurretSprite.setTexture(*Resource::resource->getTexture(this->getTurretModel()->getSprite()));
	ToolsImage::setSpriteOriginCenter(&this->mTurretSprite);
	ToolsImage::resizeSprite(&this->mTurretSprite, this->getSize(), this->getSize());
	this->setTurretScale(this->mTurretSprite.getScale().x);
	this->notifyTurretModelChanged();

	this->computeTurretRotationTick();
}

TurretEffect::~TurretEffect( void )
{
	for(int i = 0; i < this->mWeaponEffect.size(); i++)
		delete this->mWeaponEffect[i];
	this->mWeaponEffect.clear();
}

//*************************************************************
// Getters - Setters
//*************************************************************
TurretEffectModel* TurretEffect::getTurretModel()
{
	return this->mTurretModel;
}

void TurretEffect::setTurretModel( TurretEffectModel* p_model )
{
	if(this->mTurretModel = p_model)
	{
		this->mTurretModel = p_model;
		this->notifyTurretModelChanged();
	}
}

float TurretEffect::getTurretScale()
{
	return this->mTurretScale;
}

void TurretEffect::setTurretScale( float p_scale )
{
	this->mTurretScale = p_scale;
}

std::string TurretEffect::getWeaponEffectSprite()
{
	return this->mWeaponEffectSprite;
}

void TurretEffect::setWeaponEffectSprite( std::string p_sprite )
{
	this->mWeaponEffectSprite = p_sprite;
}


//*************************************************************
// Methods
//*************************************************************
void TurretEffect::update()
{
	EntityEffect::update();
	Rotable::update();
	if(this->getEntity()->isVisible())
	{
		this->updateTurret();
		this->updatePosition();

		for(int i = 0; i < this->mWeaponEffect.size(); i++)
			this->mWeaponEffect[i]->update();
	}
}

void TurretEffect::updateTurret()
{
	if(this->getEntity()->getTarget()->isEntityValid())
	{
		this->setRotationTarget(Tools::getAngle(this->getEntity()->Object::getX() + this->getOffsetXRotate(), 
												this->getEntity()->Object::getY() + this->getOffsetYRotate(), 
												this->getEntity()->getTarget()->getEntity()->getX(this->getEntity()->getPlane()), 
												this->getEntity()->getTarget()->getEntity()->getY(this->getEntity()->getPlane())) - this->getEntity()->getRotation());
		this->setRotation(this->getRotationTarget());
		this->mTurretSprite.setRotation(this->getEntity()->getRotation() + this->getRotation());
	}
	else
	{
		if(this->mTurretClock.getElapsedTimeAsSeconds() > this->mTurretRotationTick)
		{
			this->setRotationTarget(Tools::random(0, 360));
			this->computeTurretRotationTick();
			this->mTurretClock.restart();
		}
		this->mTurretSprite.setRotation(this->getEntity()->getRotation() + this->getRotation());
	}	
}

void TurretEffect::updatePosition()
{
	this->mTurretSprite.setPosition(this->getEntity()->getScreenX() + this->getOffsetXRotate(), 
									this->getEntity()->getScreenY() + this->getEntity()->getRocking() + this->getOffsetYRotate());
}

void TurretEffect::draw()
{
	EntityEffect::draw();
	if(this->getEntity()->isVisible())
	{
		Resource::resource->getApp()->draw(this->mTurretSprite);
		for(int i = 0; i < this->mWeaponEffect.size(); i++)
			this->mWeaponEffect[i]->draw();
	}
}

void TurretEffect::computeTurretRotationTick()
{
	this->mTurretRotationTick = Tools::random(TURRET_ROTATION_TICKMIN, TURRET_ROTATION_TICKMAX);
}

void TurretEffect::notifyTurretModelChanged()
{
	if(this->getTurretModel() != NULL)
	{
		for(int i = 0; i < this->getTurretModel()->getWeaponPositionCount(); i++)
		{
			sf::Vector2f currentOffset = this->getTurretModel()->getWeaponPosition(i);
			this->mWeaponEffect.push_back(new WeaponEffect(this, currentOffset.x * this->getTurretScale(), currentOffset.y * this->getTurretScale()));
		}
	}
}



