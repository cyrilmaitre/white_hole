#pragma once
#include "ItemStack.h"
#include "ContainerStackView.h"

class ContainerStack
{
public:
	// Enum
	enum ContainerStackType 
	{
		TypeCharacterShip = 0,
		TypeCharacterBank,
		TypeNone
	};

	// Constructor - Destructor
	ContainerStack(ItemStack* p_stack, int p_position, ContainerStackType p_type = ContainerStack::ContainerStackType::TypeNone);
	~ContainerStack(void);

	// Getters - Setters
	ItemStack* getItemStack();
	void setItemStack(ItemStack *p_stack, bool p_removePrec = false);
	bool hasItemStack();

	ContainerStackType getType();
	void setType(ContainerStackType p_type);

	int getPosition();
	void setPosition(int p_position);

	bool isItemTypeAllowed(ItemType* p_type);
	bool isItemStackChanged();

	// Methods
	void addItemTypeAllowed(ItemType* p_type);
	void notifyItemStackChanged();

	int incStackSize(int p_size);
	int decStackSize(int p_size);
	void setStackSize(int p_size);


private:
	// Attributs
	ItemStack* mItemStack;
	ContainerStackType mType;
	int mPosition;
	bool mItemStackChanged;
	std::vector<ItemType*> mItemTypesAllowed;
};

