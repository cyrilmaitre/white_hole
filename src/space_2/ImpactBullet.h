#pragma once
#include "Impact.h"


class ImpactBullet : public Impact
{
public:
	// Constructor - Destructor
	ImpactBullet(Entity* p_target, int p_offsetX, int p_offsetY, float p_scale = 1);
	~ImpactBullet(void);
};

