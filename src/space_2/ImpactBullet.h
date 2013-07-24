#pragma once
#include "Impact.h"


class ImpactBullet : public Impact
{
public:
	// Constructor - Destructor
	ImpactBullet(Entity* p_target, float p_scale = 1);
	~ImpactBullet(void);
};

