#pragma once
#include "EntityMovable.h"
#include "Rotable.h"
#include "Clock.h"

class Wreck;

class WreckMini : public EntityMovable
{
public:
	// Constructor - Destructor
	WreckMini(Wreck* p_parent, float p_velocity);
	~WreckMini(void);

	// Getters - Setters
	static float getQuickening();

	// Methods 
	void update();
	void update(sf::Event p_event);
	void loadSprite();
	void draw();


private:
	// Attributs
	int mSpriteId;
};

