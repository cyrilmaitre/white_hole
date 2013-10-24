#include "ContainerRestriction.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerRestriction::ContainerRestriction(void)
{
	this->mRestrictAllWhenEmpty = false;
}

ContainerRestriction::~ContainerRestriction(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool ContainerRestriction::isRestrictAllWhenEmpty()
{
	return this->mRestrictAllWhenEmpty;
}

void ContainerRestriction::setRestrictAllWhenEmpty( bool p_value )
{
	this->mRestrictAllWhenEmpty = p_value;
}

bool ContainerRestriction::isItemTypeAllowed( ItemType* p_type )
{
	if(this->mItemTypesAllowed.size() == 0)
		return !this->mRestrictAllWhenEmpty;

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


