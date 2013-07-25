#pragma once
#include "Clock.h"
#include "EntityMovableEffect.h"


class ReactorEffect : public EntityMovableEffect
{
public:
	// Enum
	enum ReactorEffectType
	{
		Left = 0,
		Right
	};

	// Constructor - Destructor
	ReactorEffect(EntityMovable* p_entity, Json::Value p_reactorJson);
	~ReactorEffect(void);

	// Getters - Setters
	ReactorEffectType getType();
	void setType(ReactorEffectType p_type);

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
	ReactorEffectType mType;
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

