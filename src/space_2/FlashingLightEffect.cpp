#include "FlashingLightEffect.h"
#include "ToolsImage.h"
#include "Tools.h"


//*************************************************************
// Define
//*************************************************************
#define JSON_COLOR					"color"
#define JSON_FLASHTICKMIN			"tickmin"
#define JSON_FLASHTICKMAX			"tickmax"
#define IMG_FLASHLIGHT				"flashinglight.png"
#define IMG_LIGHT_BLUE				"light_blue.png"
#define IMG_LIGHT_GREEN				"light_green.png"
#define IMG_LIGHT_GREY				"light_grey.png"
#define IMG_LIGHT_PURPLE			"light_purple.png"
#define IMG_LIGHT_RED				"light_red.png"
#define FLASH_SIZE_PERCENT			0.35
#define FLASH_TIME					50 //ms


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
FlashingLightEffect::FlashingLightEffect( Entity* p_entity, Json::Value p_lightJson ) : EntityEffect(p_entity, p_lightJson)
{
	this->mLightColor = (LightColor)p_lightJson.get(JSON_COLOR, 0).asInt();
	this->mFlashTickMin = p_lightJson.get(JSON_FLASHTICKMIN, 0).asFloat();
	this->mFlashTickMax = p_lightJson.get(JSON_FLASHTICKMAX, 0).asFloat();
	this->computeFlashTick();
	this->mFlashDraw = false;

	this->mLightSprite.setTexture(*Resource::resource->getTexture(this->getLightSprite()));
	ToolsImage::setSpriteOriginCenter(&this->mLightSprite);	
	ToolsImage::resizeSprite(&this->mLightSprite, this->getSize(), this->getSize());

	this->mFlashSprite.setTexture(*Resource::resource->getTexture(IMG_FLASHLIGHT));
	ToolsImage::setSpriteOriginCenter(&this->mFlashSprite);	
	ToolsImage::resizeSprite(&this->mFlashSprite, this->getSize() * FLASH_SIZE_PERCENT, this->getSize() * FLASH_SIZE_PERCENT);
}

FlashingLightEffect::~FlashingLightEffect(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string FlashingLightEffect::getLightSprite()
{
	switch(this->mLightColor)
	{
	case LightColor::Blue:
		return IMG_LIGHT_BLUE;
		break;

	case LightColor::Green:
		return IMG_LIGHT_GREEN;
		break;

	case LightColor::Grey:
		return IMG_LIGHT_GREY;
		break;

	case LightColor::Purple:
		return IMG_LIGHT_PURPLE;
		break;

	case LightColor::Red:
		return IMG_LIGHT_RED;
		break;
	}
}


//*************************************************************
// Methods
//*************************************************************
void FlashingLightEffect::update()
{
	EntityEffect::update();
	if(this->getEntity()->isVisible())
	{
		this->updatePosition();
		this->updateFlash();
	}
}

void FlashingLightEffect::updatePosition()
{
	this->mLightSprite.setPosition(	this->getEntity()->getScreenX() + this->getOffsetXRotate(), 
									this->getEntity()->getScreenY() + this->getEntity()->getRocking() + this->getOffsetYRotate());

	this->mFlashSprite.setPosition(	this->getEntity()->getScreenX() + this->getOffsetXRotate(), 
									this->getEntity()->getScreenY() + this->getEntity()->getRocking() + this->getOffsetYRotate());
}

void FlashingLightEffect::updateFlash()
{
	if(this->mFlashClock.getElapsedTimeAsMilliseconds() > this->mFlashTick)
	{
		this->mFlashDraw = true;
		this->computeFlashTick();
		this->mFlashClock.restart();
	}
	else if(this->mFlashClock.getElapsedTimeAsMilliseconds() > FLASH_TIME)
	{
		this->mFlashDraw = false;
	}
}

void FlashingLightEffect::draw()
{
	EntityEffect::draw();
	if(this->getEntity()->isVisible())
	{
		Resource::resource->getApp()->draw(this->mLightSprite);
		if(this->mFlashDraw)
			Resource::resource->getApp()->draw(this->mFlashSprite);
	}
}

void FlashingLightEffect::computeFlashTick()
{
	this->mFlashTick = Tools::random(this->mFlashTickMin, this->mFlashTickMax);
}

