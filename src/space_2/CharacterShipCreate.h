#pragma once
#include "NetworkJob.h"
#include "CharacterShip.h"

class CharacterShipCreate : public NetworkJob
{
public:
	// Constructor - Destructor
	CharacterShipCreate(CharacterShip* p_ship);
	~CharacterShipCreate(void);

	// Methods
	void job();


private:
	// Attributs
	CharacterShip* mCharacterShip;
};

