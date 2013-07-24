#pragma once
#include "CharacterShip.h"
#include "Ship.h"
#include "KeyValueFile.h"


class ShipFactory
{
public:
	static Ship* getShip(ShipModel* p_shipModel);


private:
	ShipFactory(void);
	~ShipFactory(void);
};

