#pragma once
#include "Stuffable.h"
#include "Upgradable.h"
#include "Weaponable.h"


class Equipable: public Stuffable, public Upgradable, public Weaponable
{
public:
	// Constructor - Destructor
	Equipable(void);
	~Equipable(void);
};

