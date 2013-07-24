#pragma once
#include "NetworkJob.h"
#include "ItemStack.h"

class CharacterShipItemStackUpdate : public NetworkJob
{
public:
	// Constructor - Destructor
	CharacterShipItemStackUpdate(ItemStack* p_itemStack, int p_position);
	~CharacterShipItemStackUpdate(void);

	// Methods
	void job();


private:
	// Attributs
	ItemStack* mItemStack;
	int mPosition;
};

