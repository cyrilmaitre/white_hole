#pragma once
#include "MarioGameBlockActive.h"
#include "Clock.h"


class MarioGameBrick : public MarioGameBlockActive
{
public:
	// Enum
	enum BrickState
	{
		Idle,
		EffectOne,
		EffectTwo,
		EffectThree,
		EffectFour
	};

	// Constructor - Destructor
	MarioGameBrick(MarioGame* p_game, sf::Vector2i p_positionGrid);
	~MarioGameBrick(void);

	// Getters - Setters
	BrickState getBrickState();
	void setBrickState(BrickState p_state);

	// Methods
	void update();
	void updateBrickState();
	void updateNextEffectTick();
	void notifyBrickStateChanged();


private:
	// Attributs
	BrickState mBrickState;
	mks::Clock mBrickClock;
	float mNextEffectTick;
};

