#pragma once
#include "Item.h"

// Define
#define LOOTITEMMODEL_CONFIG_ID				"id"
#define LOOTITEMMODEL_CONFIG_ITEM			"item"
#define LOOTITEMMODEL_CONFIG_QUANITYMIN		"quantity_min"
#define LOOTITEMMODEL_CONFIG_QUANITYMAX		"quantity_max"

class LootItemModel
{
public:
	// Constructor - Destructor
	LootItemModel(KeyValueFile* p_config);
	~LootItemModel(void);

	// Getters - Setters
	long getIdLootItemModel();
	void setIdLootItemModel(long p_id);

	Item* getItem();
	void setItem(Item* p_item);

	int getQuantityMin();
	void setQuantityMin(int p_min);

	int getQuantityMax();
	void setQuantityMax(int p_max);

	// Methods
	int generateQuantity();
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	long mIdLootItemModel;
	Item* mItem;
	int mQuantityMin;
	int mQuantityMax;
};

