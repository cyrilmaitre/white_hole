#pragma once
#include "EffectMap.h"
#include "ImageGIF.h"
#include "Entity.h"
#include "Clock.h"

// Define
#define SHOCKWAVE_PHASE_BEGIN		0.3		// sec

class ExplosionEffect : public EffectMap
{
public:
	// Constructor - Destructor
	ExplosionEffect(Entity* p_entity);
	~ExplosionEffect(void);

	/// Getters - Setters
	bool isFlashPhase();
	bool isShockWavePhase();

	// Methods
	void update();
	void updateFlash();
	void updateShockWave();
	void updateSprite();
	void draw();


private:
	// Attributs
	sf::Sprite mFlashSprite;
	int mFlashSize;

	sf::Sprite mShockWaveSprite;
	int mShockWaveSize;

	mks::Clock mEffectClock;
	mks::Clock mShockWaveClock;
};

