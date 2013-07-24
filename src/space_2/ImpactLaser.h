#pragma once
#include "Impact.h"


class ImpactLaser : public Impact
{
public:
	// Constructor - Destructor
	ImpactLaser(Entity* p_target, float p_scale = 1);
	~ImpactLaser(void);
};

