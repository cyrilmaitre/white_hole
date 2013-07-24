#pragma once
#include "LootItemModel.h"
#include "Factory.h"

// Define
#define LOOTITEMMODEL_CONFIG	"lootitemmodel-"

class LootItemModelFactory : public Factory<LootItemModel>
{
public:
	// Constructor - Destructor
	LootItemModelFactory(void);
	~LootItemModelFactory(void);

	// Methods
	LootItemModel *getLootItemModel(std::string p_config, bool p_useLoaded = true);
	LootItemModel *getLootItemModel(int p_id, bool p_useLoaded = true);

	// Static
	static LootItemModelFactory *mInstance;
};

