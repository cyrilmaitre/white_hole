#pragma once
#include "ItemTier.h"
#include "Factory.h"

class ItemTier;

// Define
#define ITEMTIER_CONFIG			"itemtier-"

class ItemTierFactory: public Factory<ItemTier>
{
public:
	// Constructor - Destructor
	ItemTierFactory(void);
	~ItemTierFactory(void);

	// Methods
	ItemTier *getItemTier(std::string p_configItemTier, bool p_useLoaded = true);
	ItemTier *getItemTier(int p_id, bool p_useLoaded = true);

	// Static
	static ItemTierFactory *mInstance;
};

