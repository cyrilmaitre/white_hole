#pragma once
#include "Clock.h"
#include "EntityMovableEffect.h"


class Reactor : public EntityMovableEffect
{
public:
	// Enum
	enum ReactorType
	{
		Left = 0,
		Right
	};

	// Constructor - Destructor
	Reactor(EntityMovable* p_entity, Json::Value p_reactorJson);
	~Reactor(void);

	// Getters - Setters
	ReactorType getType();
	void setType(ReactorType p_type);

	bool isActive();
	void setActve(bool p_active);

	// Methods
	void update();
	void updatePosition();
	void updateActive();
	void updateReactorAlpha();
	void updateReactorDust();
	void draw();


private:
	// Attributs
	ReactorType mType;
	bool mActive;

	sf::Sprite *mReactor;
	float mReactorAlpha;
	float mReactorAlphaSpeed;

	mks::Clock mReactorClock;
	mks::Clock mReactorDustClock;
	float mReactorDustTick;

	// Methods
	void computeReactorDustTick();
};

