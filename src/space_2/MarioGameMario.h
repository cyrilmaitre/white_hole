#pragma once
#include "MarioGame.h"
#include "Clock.h"
#include "MarioGameUserData.h"

// Define 
#define MARIOGAME_MARIO_WIDTH		32
#define MARIOGAME_MARIO_HEIGHT		32

class MarioGameMario : public MarioGameUserData
{
public:
	// Enum
	enum MarioState
	{
		Idle = 0,
		RunningOne,
		RunningTwo,
		RunningThree,
		Jumping,
		None
	};

	// Constructor - Destructor
	MarioGameMario(MarioGame* p_game);
	~MarioGameMario(void);

	// Getters - Setters
	MarioState getMarioState();
	void setMarioState(MarioState p_state);

	// Methods
	void resetPosition();
	void update();
	void updateMarioState();
	void update(sf::Event p_event);
	void draw();
	void notifyMarioStateChanged();

	void BeginContact(b2Contact* p_contact, UserDataIndex p_index);
	void PreSolve(b2Contact* p_contact, const b2Manifold* p_oldManifold, UserDataIndex p_index);


private:
	// Attributs
	MarioState mMarioState;
	bool mMarioDirection;
	MarioGame* mGame;
	b2World* mWorld;
	b2Body* mBody;
	sf::Sprite* mSprite;
	mks::Clock mClockRunning;
};

