#pragma once
#include "MapObject.h"
#include "MovableData.h"
#include "Clock.h"

// Define
/*
#define MOVABLE_VELOCITY_NUMBER		9		// Velocity for each cardinality
#define MOVABLE_MOVE_N				0
#define MOVABLE_MOVE_NE				1
#define MOVABLE_MOVE_E				2
#define MOVABLE_MOVE_SE				3
#define MOVABLE_MOVE_S				4
#define MOVABLE_MOVE_SO				5
#define MOVABLE_MOVE_O				6
#define MOVABLE_MOVE_NO				7
#define MOVABLE_MOVE_NORMAL			8
*/

class Movable : public MovableData
{
public:
	// Enum
	enum MovableMode 
	{
		ModeNormal = 0,
		ModeNormalWithoutDecelerate,
		ModeAdvanced
	};

	enum MovableCardinality
	{
		North = 0,
		NorthEast,
		East,
		SouthEast,
		South,
		SouthWest,
		West,
		NorthWest,
		Normal,
		Count
	};

	// Constructor - Destructor
	Movable(void);
	~Movable(void);

	// Getters - Setters
	float getVelocityAt(MovableCardinality p_cardinality);
	void setVelocityAt(MovableCardinality cardinality, float p_velocity);

	bool getQuickeningActiveAt(MovableCardinality p_cardinality);
	void setQuickeningActiveAt(MovableCardinality p_cardinality, bool p_value);

	float getMoveX();
	float getMoveY();

	MovableMode getMode();
	void setMode(MovableMode p_mode);

	float getDistanceBeforeDecelerate(MovableCardinality p_cardinality);
	float getDistanceXBeforeDecelerate(MovableCardinality p_cardinality);
	float getDistanceYBeforeDecelerate(MovableCardinality p_cardinality);

	bool isMoving();

	// Methods
	void update();
	virtual void updateMove();
	void resetQuickeningActive();
	void resetQuickeningClock();
	void resetVelocityClock();


protected:
	// Move management
	float mVelocity[MovableCardinality::Count];
	bool mQuickeningActive[MovableCardinality::Count];
	mks::Clock mVelocityClock;	
	mks::Clock mQuickeningClock;

	float mMoveX;
	float mMoveY;
	MovableMode mMode;

	// Methods
	void updateVelocityAt(MovableCardinality p_cardinality, bool p_inc, long p_elapsedTimeAsMillisecond);
};

