#pragma once
#include "ItemType.h"


class ContainerRestriction
{
public:
	// Constructor - Destructor
	ContainerRestriction(void);
	~ContainerRestriction(void);

	// Getters - Setters
	bool isItemTypeAllowed(ItemType* p_type);

	// Methods
	void addItemTypeAllowed(ItemType* p_type);
	void clearItemTypeAllowed();


private:
	// Attributs
	std::vector<ItemType*> mItemTypesAllowed;
};

