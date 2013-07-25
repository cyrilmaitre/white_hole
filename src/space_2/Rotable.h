#pragma once
#include "RotableData.h"
#include "Clock.h"


class Rotable : public RotableData
{
public:
	// Constructor - Destructor
	Rotable();
	~Rotable(void);

	// Getters - Setters
	float getRotation();
	void setRotation(float p_rotation);

	float getRotationTarget();
	void setRotationTarget(float p_rotation);

	// Methods
	void update();
	void updateRotation();
	virtual void notifyRotationChanged();


private:
	// Attributs
	float mRotation;
	float mRotationTarget;
	mks::Clock mRotationClock;
};

