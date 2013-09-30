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
	ItemStack(Json::Value p_json);
	ItemStack(LootItemModel* p_lootItem);
	ItemStack(Item* p_item, int p_stackSize);
	~ItemStack(void);

	// Getters - Setters
	int getIdItemStack();
	void setIdItemStack(int p_id);

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
	int mIdItemStack;
	int mStackSize;
	double mStackPrice;
	Item *mItem;
};

