#pragma once
#include "MenuQuickItem.h"


class MenuQuickShip : public MenuQuickItem
{
public:
	// Constructor - Destructor
	MenuQuickShip(void);
	~MenuQuickShip(void);

	// Methods
	void notifyItemClicked();
};

