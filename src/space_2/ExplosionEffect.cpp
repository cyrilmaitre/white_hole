#include "ExplosionEffect.h"
#include "ImageGIFFactory.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define FLASH_SPRITE					"explosion_flash.png"
#define FLASH_SCALE						5		
#define FLASH_SCALE_MIN					4
#define FLASH_PHASE_BEGIN				0.f		// sec
#define FLASH_PHASE_OFFSETSCALE			0.25	// sec
#define FLASH_PHASE_END					0.6		// sec
#define SHOCKWAVE_SPRITE				"explosion_shockwave.png"
#define SHOCKWAVE_SPEED					1000	// px per sec
#define SHOCKWAVE_PHASE_BEGIN			0.3		// sec
#define SHOCKWAVE_PHASE_OFFSETALPHA		0.8		// sec
#define SHOCKWAVE_PHASE_DURATION		2.5		// sec
#define EXPLOSION_LIFETIME				5000	// millisec


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

	this->mShockWaveSize = 0;
	this->mShockWaveSprite.setTexture(*Resource::resource->getTexture(SHOCKWAVE_SPRITE));
	ToolsImage::setSpriteOriginCenter(&this->mShockWaveSprite);
	ToolsImage::resizeSprite(&this->mShockWaveSprite, this->mShockWaveSize, this->mShockWaveSize);

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

bool ExplosionEffect::isShockWavePhase()
{
	return this->mEffectClock.getElapsedTimeAsSeconds() > SHOCKWAVE_PHASE_BEGIN && this->mEffectClock.getElapsedTimeAsSeconds() < (SHOCKWAVE_PHASE_BEGIN + SHOCKWAVE_PHASE_DURATION);
}


//*************************************************************
// Methods
//*************************************************************
void ExplosionEffect::update()
{
	EffectMap::update();
	if(this->isFlashPhase())
		this->updateFlash();

	if(this->isShockWavePhase())
		this->updateShockWave();

	this->mShockWaveClock.restart();
}

void ExplosionEffect::updateFlash()
{
	if(this->mEffectClock.getElapsedTimeAsSeconds() > FLASH_PHASE_OFFSETSCALE)
	{
		int newSize = this->mFlashSize * (1 - (this->mEffectClock.getElapsedTimeAsSeconds() - FLASH_PHASE_OFFSETSCALE) / (FLASH_PHASE_END - FLASH_PHASE_BEGIN - FLASH_PHASE_OFFSETSCALE));
		if(newSize < this->mFlashSize / FLASH_SCALE_MIN)
			newSize = this->mFlashSize / FLASH_SCALE_MIN;
		ToolsImage::resizeSprite(&this->mFlashSprite, newSize, newSize);
	}
}

void ExplosionEffect::updateShockWave()
{
	// Size
	this->mShockWaveSize += this->mShockWaveClock.getElapsedTimeAsSeconds() * SHOCKWAVE_SPEED;
	ToolsImage::resizeSprite(&this->mShockWaveSprite, this->mShockWaveSize, this->mShockWaveSize);

	// Alpha
	if(this->mEffectClock.getElapsedTimeAsSeconds() > SHOCKWAVE_PHASE_OFFSETALPHA)
	{
		int newAlpha = 255 - (255 * ((this->mEffectClock.getElapsedTimeAsSeconds() - SHOCKWAVE_PHASE_OFFSETALPHA) / (SHOCKWAVE_PHASE_BEGIN + SHOCKWAVE_PHASE_DURATION - SHOCKWAVE_PHASE_OFFSETALPHA)));
		this->mShockWaveSprite.setColor(sf::Color(255, 255, 255, newAlpha));
	}
}

void ExplosionEffect::updateSprite()
{
	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	this->mFlashSprite.setPosition(objectPositionScreen.x, objectPositionScreen.y);
	this->mShockWaveSprite.setPosition(objectPositionScreen.x, objectPositionScreen.y);
}

void ExplosionEffect::draw()
{
	if(this->isVisible())
	{
		if(!this->isFinished())
		{
			if(this->isShockWavePhase())
				Resource::resource->getApp()->draw(this->mShockWaveSprite);

			if(this->isFlashPhase())
				Resource::resource->getApp()->draw(this->mFlashSprite);
		}	
	}
}





