#include "ItemStack.h"
#include "FactoryGet.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ItemStack::ItemStack() : mItem(NULL)
{
	this->mId = -1;
	this->mStackSize = 0;
	this->mStackPrice = 0;
}

ItemStack::ItemStack(Json::Value p_json) : mItem(NULL)
{
	this->mId = -1;
	this->mStackSize = 0;
	this->mStackPrice = 0;

	this->loadFromJson(p_json);
}

ItemStack::ItemStack( LootItemModel* p_lootItem ) : mItem(NULL)
{
	this->mId = -1;
	this->mStackSize = 0;
	this->mStackPrice = 0;

	if(p_lootItem != NULL)
	{
		this->setStackSize(p_lootItem->generateQuantity());
		this->setItem(p_lootItem->getItem());
	}
}

ItemStack::ItemStack( Item* p_item, int p_stackSize )
{
	this->mId = -1;
	this->mStackSize = 0;
	this->mStackPrice = 0;

	this->setStackSize(p_stackSize);
	this->setItem(p_item);
}

ItemStack::~ItemStack(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int ItemStack::getId()
{
	return this->mId;
}

void ItemStack::setId(int p_id)
{
	this->mId = p_id;
}

int ItemStack::getStackSize()
{
	return this->mStackSize;
}

void ItemStack::setStackSize( int p_size )
{
	this->mStackSize = p_size;
	this->notifyStackSizeChanged();
}

int ItemStack::getStackSizeFree()
{
	return this->getItem()->getStackMax() - this->mStackSize;
}

double ItemStack::getStackPrice()
{
	return this->mStackPrice;
}

void ItemStack::setStackPrice( double p_price )
{
	this->mStackPrice = p_price;
}

Item* ItemStack::getItem()
{
	return this->mItem;
}

void ItemStack::setItem(Item* p_item)
{
	this->mItem = p_item;
	this->notifyItemChanged();
}


//*************************************************************
// Methods
//*************************************************************
void ItemStack::notifyItemChanged()
{
	this->updateStackPrice();
}

void ItemStack::notifyStackSizeChanged()
{
	this->updateStackPrice();
}

void ItemStack::updateStackPrice()
{
	if(this->mItem != NULL)
		this->setStackPrice(this->getItem()->getPrice() * this->getStackSize());
}

// Return rest after inc
int ItemStack::incStackSize( int p_inc )
{
	int realInc = this->getStackSizeFree();
	if(p_inc < realInc)
		realInc = p_inc;

	this->setStackSize(this->getStackSize() + realInc);
	return p_inc - realInc;
}

// Return rest after dec
int ItemStack::decStackSize( int p_dec )
{
	int realDec = this->getStackSize();
	if(p_dec < realDec)
		realDec = p_dec;

	this->setStackSize(this->getStackSize() - realDec);
	return p_dec - realDec;
}

void ItemStack::loadFromJson( Json::Value json )
{
	if(json != NULL)
	{
		this->setId(json.get(ITEMSTACK_JSON_IDITEMSTACK, -1).asInt());
		this->setStackSize(json.get(ITEMSTACK_JSON_STACKSIZE, -1).asInt());
		this->setItem(FactoryGet::getItemFactory()->getItem(json.get(ITEMSTACK_JSON_IDITEM, 0).asInt()));
	}
}

Json::Value ItemStack::saveToJson()
{
	Json::Value json;
	json[ITEMSTACK_JSON_IDITEMSTACK] = this->getId();
	json[ITEMSTACK_JSON_STACKSIZE] = this->getStackSize();
	json[ITEMSTACK_JSON_IDITEM] = this->getItem() != NULL ? this->getItem()->getId() : -1;
	return json;
}




