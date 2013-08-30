#pragma once
#include "Resource.h"
#include "Clock.h"

// Define
#define ROCKING_PERIOD					0.3	// Sec
#define ROCKING_AMPLITUDE				5
#define ROCKING_CYCLE					ROCKING_AMPLITUDE * ROCKING_PERIOD * 4
#define ROCKING_CYCLE_DEMI				ROCKING_CYCLE / 2
#define ROCKING_CYCLE_DEMI_OFFSET		ROCKING_CYCLE_DEMI / ROCKING_PERIOD

class Rockable
{
public:
	// Constructor - Destructor
	Rockable(void);
	~Rockable(void);

	// Getters - Setters
	float getRocking();

	bool isRockingActived();
	void setRockingActived(bool p_actived);

	// Methods
	void update();
	virtual void updateRocking();


private:
	// Attributs
	mks::Clock mRockingClock;
	float mRocking;
	bool mRockingActived;
};

