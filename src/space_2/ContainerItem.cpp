#include "ContainerItem.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerItem::ContainerItem( Item* p_item ) : mItem(NULL)
{
	this->mItem = p_item;
	this->mItemChanged = false;
}

ContainerItem::~ContainerItem(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Item* ContainerItem::getItem()
{
	return this->mItem;
}

void ContainerItem::setItem( Item* p_item, bool p_removePrec, bool p_notify )
{
	if(this->mItem != p_item)
	{
		if(p_removePrec && this->mItem != NULL)
			delete this->mItem;

		this->mItem = p_item;
		if(p_notify)
			this->notifyItemChanged();
	}
}

bool ContainerItem::hasItem()
{
	return this->mItem != NULL;
}

bool ContainerItem::isItemChanged()
{
	bool returnValue = this->mItemChanged;
	this->mItemChanged = false;
	return returnValue;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerItem::notifyItemChanged()
{
	this->mItemChanged = true;
}
