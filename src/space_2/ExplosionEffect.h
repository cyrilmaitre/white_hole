#pragma once
#include "EffectMap.h"
#include "ImageGIF.h"
#include "Entity.h"
#include "Clock.h"


class ExplosionEffect : public EffectMap
{
public:
	// Constructor - Destructor
	ExplosionEffect(Entity* p_entity);
	~ExplosionEffect(void);

	/// Getters - Setters
	bool isFlashPhase();
	float getFlashPhaseDuration();
	float getFlashPhaseProgress();

	bool isShockWavePhase();
	float getShockWaveDuration();
	float getShockWaveprogress();


	// Methods
	void update();
	void updateFlash();
	void updateSprite();
	void draw();


private:
	// Attributs
	sf::Sprite mFlashSprite;
	int mFlashSize;

	mks::Clock mEffectClock;
};

