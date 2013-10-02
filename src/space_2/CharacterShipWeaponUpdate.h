#pragma once
#include "CharacterShip.h"
#include "NetworkJob.h"


class CharacterShipWeaponUpdate : public NetworkJob
{
public:
	// Constructor - Destructor
	CharacterShipWeaponUpdate(CharacterShip* p_ship);
	~CharacterShipWeaponUpdate(void);

	// Methods
	void job();


private:
	// Attributs
	CharacterShip* mCharacterShip;
};

