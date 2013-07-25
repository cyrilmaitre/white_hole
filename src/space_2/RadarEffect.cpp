#include "RadarEffect.h"
#include "ToolsImage.h"
#include "Tools.h"


//*************************************************************
// Define
//*************************************************************
#define JSON_TYPE					"type"
#define JSON_ROTATIONVELOCITY		"rotationvelocity"
#define JSON_SPRITE					"sprite"
#define SPRITE_DEFAULT				"radar_1.png"
#define RADAR_ROTATION_TICKMIN		3.f	// sec
#define RADAR_ROTATION_TICKMAX		6.f // sec


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
RadarEffect::RadarEffect( Entity* p_entity, Json::Value p_radarJson ) : EntityEffect(p_entity, p_radarJson)
{
	this->setRadarType((RadarEffectType)p_radarJson.get(JSON_TYPE, 0).asInt());
	this->setRotationVelocity(p_radarJson.get(JSON_ROTATIONVELOCITY, 0).asFloat());

	this->mRadarSprite.setTexture(*Resource::resource->getTexture(p_radarJson.get(JSON_SPRITE, SPRITE_DEFAULT).asString()));
	ToolsImage::setSpriteOriginCenter(&this->mRadarSprite);
	ToolsImage::resizeSprite(&this->mRadarSprite, this->getSize(), this->getSize());

	this->computeRadarRotationTick();
}

RadarEffect::~RadarEffect(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
RadarEffect::RadarEffectType RadarEffect::getRadarType()
{
	return this->mRadarType;
}

void RadarEffect::setRadarType( RadarEffectType p_type )
{
	if(this->mRadarType != p_type)
	{
		this->mRadarType = p_type;
		this->notifyRadarTypeChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void RadarEffect::update()
{
	EntityEffect::update();
	Rotable::update();
	if(this->getEntity()->isVisible())
	{
		this->updateRadar();
		this->updatePosition();
	}
}

void RadarEffect::updateRadar()
{
	if(this->getRadarType() == RadarEffectType::Normal)
	{
		if(this->mRadarClock.getElapsedTimeAsSeconds() > this->mRadarRotationTick)
		{
			this->setRotationTarget(Tools::random(0, 360));
			this->computeRadarRotationTick();
			this->mRadarClock.restart();
		}
	}

	this->mRadarSprite.setRotation(this->getEntity()->getRotation() + this->getRotation());
}

void RadarEffect::updatePosition()
{
	this->mRadarSprite.setPosition(	this->getEntity()->getScreenX() + this->getOffsetXRotate(), 
									this->getEntity()->getScreenY() + this->getEntity()->getRocking() + this->getOffsetYRotate());
}

void RadarEffect::draw()
{
	EntityEffect::draw();
	if(this->getEntity()->isVisible())
	{
		Resource::resource->getApp()->draw(this->mRadarSprite);
	}
}

void RadarEffect::notifyRadarTypeChanged()
{
	if(this->mRadarType == RadarEffectType::Normal)
	{
		this->setRotationInfinite(false);
	}
	else
	{
		this->setRotationInfinite(true);
		this->setRotationInfiniteRight(Tools::randomBool());
	}
}

void RadarEffect::computeRadarRotationTick()
{
	this->mRadarRotationTick = Tools::random(RADAR_ROTATION_TICKMIN, RADAR_ROTATION_TICKMAX);
}
