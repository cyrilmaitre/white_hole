#include "ExplosionEffect.h"
#include "ImageGIFFactory.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define FLASH_SPRITE				"explosion_flash.png"
#define FLASH_SCALE					4		
#define FLASH_SCALE_MIN				2		
#define FLASH_PHASE_BEGIN			0.f		// sec
#define FLASH_PHASE_END				0.75	// sec
#define SHOCKWAVE_PHASE_BEGIN		0.5		// sec
#define SHOCKWAVE_PHASE_END			2.f		// sec
#define EXPLOSION_LIFETIME			5000	// millisec


//*************************************************************
// Constructor - Destructor
//*************************************************************
ExplosionEffect::ExplosionEffect(Entity* p_entity)
{
	this->mLiveTime = 0;
	
	this->mFlashSize = p_entity->getRadius() * FLASH_SCALE;
	this->mFlashSprite.setTexture(*Resource::resource->getTexture(FLASH_SPRITE));
	ToolsImage::setSpriteOriginCenter(&this->mFlashSprite);
	ToolsImage::resizeSprite(&this->mFlashSprite, this->mFlashSize, this->mFlashSize);

	this->setLiveTime(EXPLOSION_LIFETIME);
	this->setSize(p_entity->Object::getWidth(), p_entity->Object::getHeight());
	this->setPosition(p_entity->Object::getX(), p_entity->Object::getY());
}

ExplosionEffect::~ExplosionEffect(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool ExplosionEffect::isFlashPhase()
{
	return this->mEffectClock.getElapsedTimeAsSeconds() > FLASH_PHASE_BEGIN && this->mEffectClock.getElapsedTimeAsSeconds() < FLASH_PHASE_END;
}

float ExplosionEffect::getFlashPhaseDuration()
{
	return FLASH_PHASE_END - FLASH_PHASE_BEGIN;
}

float ExplosionEffect::getFlashPhaseProgress()
{
	if(this->mEffectClock.getElapsedTimeAsSeconds() < FLASH_PHASE_BEGIN)
		return 0.f;
	else if(this->mEffectClock.getElapsedTimeAsSeconds() > FLASH_PHASE_END)
		return 1.f;
	else
		return (this->mEffectClock.getElapsedTimeAsSeconds() - FLASH_PHASE_BEGIN) / this->getFlashPhaseDuration();
}

bool ExplosionEffect::isShockWavePhase()
{
	return this->mEffectClock.getElapsedTimeAsSeconds() > SHOCKWAVE_PHASE_BEGIN && this->mEffectClock.getElapsedTimeAsSeconds() < SHOCKWAVE_PHASE_END;
}

float ExplosionEffect::getShockWaveDuration()
{
	return SHOCKWAVE_PHASE_END - SHOCKWAVE_PHASE_BEGIN;
}

float ExplosionEffect::getShockWaveprogress()
{
	if(this->mEffectClock.getElapsedTimeAsSeconds() < SHOCKWAVE_PHASE_BEGIN)
		return 0.f;
	else if(this->mEffectClock.getElapsedTimeAsSeconds() > SHOCKWAVE_PHASE_END)
		return 1.f;
	else
		return (this->mEffectClock.getElapsedTimeAsSeconds() - SHOCKWAVE_PHASE_BEGIN) / this->getShockWaveDuration();
}


//*************************************************************
// Methods
//*************************************************************
void ExplosionEffect::update()
{
	EffectMap::update();
	if(this->isFlashPhase())
		this->updateFlash();
}

void ExplosionEffect::updateFlash()
{
	int newSize = this->mFlashSize * (1 - this->getFlashPhaseProgress());
	if(newSize < this->mFlashSize / FLASH_SCALE_MIN)
		newSize = this->mFlashSize / FLASH_SCALE_MIN;
	ToolsImage::resizeSprite(&this->mFlashSprite, newSize, newSize);
}

void ExplosionEffect::updateSprite()
{
	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	this->mFlashSprite.setPosition(objectPositionScreen.x, objectPositionScreen.y);
}

void ExplosionEffect::draw()
{
	if(this->isVisible())
	{
		if(!this->isFinished())
		{
			if(this->isFlashPhase())
				Resource::resource->getApp()->draw(this->mFlashSprite);
		}	
	}
}





