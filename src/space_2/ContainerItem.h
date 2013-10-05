#pragma once
#include "ContainerRestriction.h"
#include "Item.h"


class ContainerItem : public ContainerRestriction
{
public:
	// Constructor - Destructor
	ContainerItem(Item* p_item = NULL);
	~ContainerItem(void);

	// Getters - Setters
	Item* getItem();
	void setItem(Item* p_item, bool p_removePrec = false, bool p_notify = true);
	bool hasItem();
	bool isItemChanged();

	// Methods
	virtual void notifyItemChanged();


private:
	// Attributs
	Item* mItem;
	bool mItemChanged;
};

