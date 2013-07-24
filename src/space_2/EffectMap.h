#pragma once
#include "MapObject.h"
#include "Effect.h"

// Define
#define EFFECTMAP_PLANE		MAPOBJECT_PLANE_1

class EffectMap : public Effect, public MapObject
{
public:
	// Constructor - Destructor
	EffectMap(int p_plane = EFFECTMAP_PLANE);
	~EffectMap(void);

	// Methods
	virtual void update();
};

