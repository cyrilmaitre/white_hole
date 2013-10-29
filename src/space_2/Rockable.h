#pragma once
#include "Resource.h"
#include "Clock.h"


class Rockable
{
public:
	// Enum
	enum RockingState
	{
		ActiveUp,
		ActiveDown,
		Inactive
	};

	// Constructor - Destructor
	Rockable(void);
	~Rockable(void);

	// Getters - Setters
	float getRocking();
	void setRocking(float p_rocking);

	RockingState getRockingState();
	void setRockingState(RockingState p_state);

	// Methods
	void update();
	virtual void updateRocking();


protected:
	// Attributs
	float mRocking;
	RockingState mRockingState;
	mks::Clock mRockingClock;
};

