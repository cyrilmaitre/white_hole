#pragma once
#include "CharacterShip.h"
#include "NetworkJob.h"


class CharacterShipWeaponCreate : public NetworkJob
{
public:
	// Constructor - Destructor
	CharacterShipWeaponCreate(CharacterShip* p_ship);
	~CharacterShipWeaponCreate(void);

	// Methods
	void job();


private:
	// Attributs
	CharacterShip* mCharacterShip;
};

