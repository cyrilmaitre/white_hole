#pragma once
#include "Impact.h"

class ImpactExplosion : public Impact
{
public:
	// Constructor - Destructor
	ImpactExplosion(Entity* p_target, float p_scale = 1);
	~ImpactExplosion(void);
};

