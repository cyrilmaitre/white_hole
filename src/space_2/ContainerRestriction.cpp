#include "ContainerRestriction.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerRestriction::ContainerRestriction(void)
{
}

ContainerRestriction::~ContainerRestriction(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool ContainerRestriction::isItemTypeAllowed( ItemType* p_type )
{
	if(this->mItemTypesAllowed.size() == 0)
		return true;

	for(int i = 0; i < this->mItemTypesAllowed.size(); i++)
	{
		if(this->mItemTypesAllowed[i] != NULL && p_type != NULL && p_type->isChildOf(this->mItemTypesAllowed[i]))
			return true;
	}

	return false;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerRestriction::addItemTypeAllowed( ItemType* p_type )
{
	this->mItemTypesAllowed.push_back(p_type);
}

void ContainerRestriction::clearItemTypeAllowed()
{
	this->mItemTypesAllowed.clear();
}