#pragma once
#include "NetworkJob.h"
#include "ItemStack.h"
#include "CharacterBank.h"


class CharacterBankItemStackUpdate : public NetworkJob
{
public:
	// Constructor - Destructor
	CharacterBankItemStackUpdate(CharacterBank* p_bank, ItemStack* p_itemStack, int p_position);
	~CharacterBankItemStackUpdate(void);

	// Methods
	void job();


private:
	// Attributs
	CharacterBank* mCharacterBank;
	ItemStack* mItemStack;
	int mPosition;
};

