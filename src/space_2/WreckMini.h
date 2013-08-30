#pragma once
#include "EntityMovable.h"
#include "Rotable.h"
#include "Clock.h"

class Wreck;

class WreckMini : public EntityMovable
{
public:
	// Constructor - Destructor
	WreckMini(Wreck* p_parent);
	~WreckMini(void);


	// Methods 
	void update();
	void update(sf::Event p_event);
	void updateSprite();
	void loadSprite();
	void draw();


private:
	// Attributs
	int mSpriteId;
	mks::Clock mWreckMiniClock;
};

