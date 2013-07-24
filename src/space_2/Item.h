#pragma once
#include "ItemTierFactory.h"
#include "ItemTypeFactory.h"
#include "KeyValueFile.h"

// Define
#define ITEM_CONFIG_ID				"id"
#define ITEM_CONFIG_NAME			"name"
#define ITEM_CONFIG_DESCRIPTION		"description"
#define ITEM_CONFIG_PRICE			"price"
#define ITEM_CONFIG_STACKMAX		"stackmax"
#define ITEM_CONFIG_SPRITE			"sprite"
#define ITEM_CONFIG_ITEMTYPE		"itemtype"
#define ITEM_CONFIG_ITEMTIER		"itemtier"

class Item
{
public:
	// Constructor - Destructor
	Item(KeyValueFile *p_config);
	Item(int p_id);
	virtual ~Item(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_description);

	double getPrice();
	void setPrice(double p_price);

	int getStackMax();
	void setStackMax(int p_max);

	std::string getSpriteId();
	void setSpriteId(std::string p_sprite);

	ItemType* getItemType();
	void setItemType(ItemType *p_itemType);

	ItemTier* getItemTier();
	void setItemTier(ItemTier *p_itemTier);

	// Methode
	void loadFromConfig(KeyValueFile *p_config);


private:
	// Attributes
	long mId;
	std::string mName;
	std::string mDescription;
	double mPrice;
	int mStackMax;
	std::string mSpriteId;

	ItemType *mItemType;
	ItemTier *mItemTier;
};

