#pragma once
#include "EffectMap.h"
#include "ImageGIF.h"
#include "Entity.h"

class ExplosionEffect : public EffectMap
{
public:
	// Constructor - Destructor
	ExplosionEffect(Entity* p_entity);
	~ExplosionEffect(void);

	// Methods
	void update();
	void updatePosition();
	void draw();


private:
	// Attributs
	ImageGIF *mExplosionGif;

	// Methods
	void configureExplosion(Entity* p_entity);
};

