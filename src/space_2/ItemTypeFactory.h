#pragma once
#include "ItemType.h"
#include "Factory.h"

class ItemType;

// Define
#define ITEMTYPE_CONFIG		"itemtype-"

class ItemTypeFactory: public Factory<ItemType>
{
public:
	// Constructor - Destructor
	ItemTypeFactory(void);
	~ItemTypeFactory(void);

	// Methods
	ItemType *getItemType(std::string p_configItemType, bool p_useLoaded = true);
	ItemType *getItemType(int p_id, bool p_useLoaded = true);

	// Static
	static ItemTypeFactory* mInstance;
};

