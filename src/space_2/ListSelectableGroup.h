#pragma once
#include "List.h"
#include "SelectableGroup.h"


class ListSelectableGroup : public List, public SelectableGroup
{
public:
	// Constructor - Destructor
	ListSelectableGroup(bool p_selectedCanBeNull = false);
	~ListSelectableGroup(void);

	// Methods
	void update(sf::Event p_event);
	void selectNextItem();
	void selectPreviousItem();
	void notifyItemAdded(Listable *p_item);
	void notifyItemRemoved(Listable *p_item);
};

