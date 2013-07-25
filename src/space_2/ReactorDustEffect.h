#pragma once
#include "EffectMap.h"
#include "Clock.h"


class ReactorDustEffect : public EffectMap
{
public:
	// Constructor - Destructor
	ReactorDustEffect(double p_x, double p_y, float p_size, float p_alpha);
	~ReactorDustEffect(void);

	// Methods
	void update();
	void updateSpriteSize();
	void loadSprite();


private:
	// Atrributs
	float mSize;
	float mAlpha;
	mks::Clock mClockReactorDust;
};

