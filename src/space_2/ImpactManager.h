#pragma once
#include "Impact.h"


class ImpactManager
{
public:
	// Methods
	static Impact* getImpact(Impact::ImpactType p_type, Entity* p_target, float p_scale = 1);

private:
	// Constructor - Destructor
	ImpactManager(void);
	~ImpactManager(void);
};

