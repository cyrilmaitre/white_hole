#pragma once
#include "NetworkJob.h"
#include "CharacterShip.h"


class CharacterShipRemove : public NetworkJob
{
public:
	// Constructor - Destructor
	CharacterShipRemove(CharacterShip* p_ship);
	~CharacterShipRemove(void);

	// Methods
	void job();


private:
	CharacterShip* mCharacterShip;
};

