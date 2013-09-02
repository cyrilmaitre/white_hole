#pragma once
#include "EntityMovable.h"
#include "Rotable.h"
#include "Clock.h"

class Wreck;

class WreckMini : public EntityMovable
{
public:
	// Enum
	enum EmberAlphaState
	{
		Stopped,
		Up,
		Down
	};

	// Constructor - Destructor
	WreckMini(Wreck* p_parent);
	~WreckMini(void);


	// Methods 
	void update();
	void update(sf::Event p_event);
	void updateSprite();
	void updateEmber();
	void loadSprite();
	void unloadSprite();
	void notifyRotationChanged();
	void draw();


private:
	// Attributs
	int mSpriteId;

	sf::Sprite* mEmberSprite;
	float mEmberAlpha;
	float mEmberAlphaNextTick;
	EmberAlphaState mEmberAlphaState;
	mks::Clock mEmberAlphaClock;
	mks::Clock mEmberAlphaTickClock;


	// Methods
	void computeEmberAlphaNextTick();
};

