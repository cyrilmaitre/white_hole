#pragma once
#include "Impact.h"

class ImpactExplosion : public Impact
{
public:
	// Constructor - Destructor
	ImpactExplosion(Entity* p_target, int p_offsetX, int p_offsetY, float p_scale = 1);
	~ImpactExplosion(void);
};

