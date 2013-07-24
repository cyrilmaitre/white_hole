#pragma once
#include "NetworkJob.h"
#include "Character.h"


class CharacterUpdate : public NetworkJob
{
public:
	// Constructor - Destructor
	CharacterUpdate(Character* p_character);
	~CharacterUpdate(void);

	// Methods
	void job();


private:
	// Attributs
	Character* mCharacter;
};

