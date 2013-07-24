#pragma once
#include "Factory.h"
#include "Item.h"

class Item;

// Define
#define ITEM_CONFIG		"item-"

class ItemFactory: public Factory<Item>
{
public:
	// Constructor - Destructor
	ItemFactory(void);
	~ItemFactory(void);

	// Methods
	Item *getItem(std::string p_config, bool p_useLoaded = true);
	Item *getItem(int p_id, bool p_useLoaded = true);

	// Static
	static ItemFactory* mInstance;
};

