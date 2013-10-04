#pragma once
#include "ItemStack.h"
#include "ContainerStackView.h"
#include "ContainerRestriction.h"

class ContainerRow;

class ContainerStack : public ContainerRestriction
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
	ContainerStack(ContainerRow* p_parent, ItemStack* p_stack, int p_position, ContainerStackType p_type = ContainerStack::ContainerStackType::TypeNone);
	ContainerStack(ItemStack* p_stack = NULL);
	~ContainerStack(void);

	// Getters - Setters
	ContainerRow* getContainerRow();

	ItemStack* getItemStack();
	void setItemStack(ItemStack *p_stack, bool p_removePrec = false, bool p_notify = true);
	bool hasItemStack();
	bool isItemStackChanged();

	ContainerStackType getType();
	void setType(ContainerStackType p_type);

	int getPosition();
	void setPosition(int p_position);

	// Methods
	int incStackSize(int p_size, bool p_notify = true);
	int decStackSize(int p_size, bool p_notify = true);
	void setStackSize(int p_size, bool p_notify = true);

	void notifyItemStackChanged();


private:
	// Attributs
	ContainerRow* mContainerRow;
	ItemStack* mItemStack;
	ContainerStackType mType;
	int mPosition;
	bool mItemStackChanged;
};

