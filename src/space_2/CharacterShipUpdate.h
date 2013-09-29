#pragma once
#include "NetworkJob.h"
#include "CharacterShip.h"


class CharacterShipUpdate : public NetworkJob
{
public:
	// Constructor - Destructor
	CharacterShipUpdate(CharacterShip* p_ship);
	~CharacterShipUpdate(void);

	// Methods
	void job();


private:
	// Attributs
	CharacterShip* mCharacterShip;
};

