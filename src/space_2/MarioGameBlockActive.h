#pragma once
#include "MarioGameBlock.h"
#include "MarioGameUserData.h"
#include "Clock.h"


class MarioGameBlockActive : public MarioGameUserData, public MarioGameBlock
{
public:
	// Enum
	enum ActiveState
	{
		Idle,
		Upped,
		Downed
	};

	// Constructor - Destructor
	MarioGameBlockActive(MarioGame* p_game, sf::Vector2i p_positionGrid);
	~MarioGameBlockActive(void);

	// Getters - Setters
	ActiveState getActiveState();
	void setActiveState(ActiveState p_state);

	// Methods
	void update();
	void updateActiveState();
	void BeginContact(b2Contact* p_contact, MarioGameUserData::UserDataIndex p_index);


protected:
	// Attributs
	b2Body* mBodyBrick;
	ActiveState mActiveState;
	mks::Clock mActiveClock;
};

