#pragma once
#include "Item.h"
#include "LootItemModel.h"

// Define
#define ITEMSTACK_JSON_IDITEMSTACK		"idItemStack"
#define ITEMSTACK_JSON_STACKSIZE		"stackSize"
#define ITEMSTACK_JSON_IDITEM			"idItem"

class ItemStack
{
public:
	// Constructor - Destructor
	ItemStack();
	ItemStack(Json::Value json);
	ItemStack(LootItemModel* lootItem);
	~ItemStack(void);

	// Getters - Setters
	int getId();
	void setId(int p_id);

	int getStackSize();
	void setStackSize(int p_size);

	int getStackSizeFree();

	double getStackPrice();
	void setStackPrice(double p_price);

	Item* getItem();
	void setItem(Item* p_item);

	// Methods
	void notifyItemChanged();
	void notifyStackSizeChanged();
	void updateStackPrice();
	int incStackSize(int p_inc);
	int decStackSize(int p_dec);

	void loadFromJson(Json::Value json);
	Json::Value saveToJson();


private:
	// Attributs
	int mId;
	int mStackSize;
	double mStackPrice;
	Item *mItem;
};

