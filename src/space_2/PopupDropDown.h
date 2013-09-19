#pragma once
#include "ListSelectableGroup.h"


class PopupDropDown : public ListSelectableGroup
{
public:
	// Constructor - Destructor
	PopupDropDown(void);
	~PopupDropDown(void);

	// Methods
	void update(sf::Event p_event);
	void notifyVisibleChanged();
	void notifySelectionChanged();
};

