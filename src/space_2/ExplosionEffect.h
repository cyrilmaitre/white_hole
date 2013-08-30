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
	ExplosionEffect(Entity* p_entity, bool p_shockWave = true, bool p_flash = true);
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
	bool mFlash;

	sf::Sprite mShockWaveSprite;
	int mShockWaveSize;
	bool mShockWave;

	mks::Clock mEffectClock;
	mks::Clock mShockWaveClock;
};

