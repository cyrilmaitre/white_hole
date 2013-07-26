#include "TurretEffect.h"
#include "Tools.h"
#include "ToolsImage.h"
#include "ToolsMap.h"


//*************************************************************
// Define
//*************************************************************
#define JSON_ROTATIONVELOCITY		"rotationvelocity"
#define JSON_SPRITE					"sprite"
#define SPRITE_DEFAULT				"turret_one_1.png"
#define TURRET_ROTATION_TICKMIN		3.f	// sec
#define TURRET_ROTATION_TICKMAX		6.f // sec


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
TurretEffect::TurretEffect( Entity* p_entity, Json::Value p_turretJson ) : EntityEffect(p_entity, p_turretJson)
{
	this->setRotationVelocity(p_turretJson.get(JSON_ROTATIONVELOCITY, 0).asFloat());

	this->mTurretSprite.setTexture(*Resource::resource->getTexture(p_turretJson.get(JSON_SPRITE, SPRITE_DEFAULT).asString()));
	ToolsImage::setSpriteOriginCenter(&this->mTurretSprite);
	ToolsImage::resizeSprite(&this->mTurretSprite, this->getSize(), this->getSize());

	this->computeTurretRotationTick();
}

TurretEffect::~TurretEffect( void )
{

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
	}
}

void TurretEffect::updateTurret()
{
	if(this->getEntity()->getTarget()->isEntityValid())
	{
		this->setRotationTarget(Tools::getAngle(this->getEntity()->Object::getX() + this->getOffsetXRotate(), 
												this->getEntity()->Object::getY() + this->getOffsetYRotate(), 
												this->getEntity()->getTarget()->getEntity()->getX(this->getEntity()->getPlane()), 
												this->getEntity()->getTarget()->getEntity()->getY(this->getEntity()->getPlane())));
		this->setRotation(this->getRotationTarget());
		this->mTurretSprite.setRotation(this->getRotation());
	}
	else
	{
		if(this->mTurrentClock.getElapsedTimeAsSeconds() > this->mTurretRotationTick)
		{
			this->setRotationTarget(Tools::random(0, 360));
			this->computeTurretRotationTick();
			this->mTurrentClock.restart();
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
	}
}

void TurretEffect::computeTurretRotationTick()
{
	this->mTurretRotationTick = Tools::random(TURRET_ROTATION_TICKMIN, TURRET_ROTATION_TICKMAX);
}