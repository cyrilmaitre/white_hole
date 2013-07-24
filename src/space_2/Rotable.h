#pragma once
#include "RotableData.h"
#include "MapObject.h"
#include "Clock.h"


class Rotable : public RotableData
{
public:
	// Constructor - Destructor
	Rotable(MapObject* p_object);
	~Rotable(void);

	// Getters - Setters
	float getRotationTarget();
	void setRotationTarget(float p_rotation);

	// Methods
	void update();
	void updateRotation();


private:
	// Attributs
	MapObject* mMapObject;
	float mRotationTarget;
	mks::Clock mRotationClock;
};

