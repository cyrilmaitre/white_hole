#pragma once
#include "MenuQuickItem.h"


class MenuQuickCargo : public MenuQuickItem
{
public:
	// Constructor - Destructor
	MenuQuickCargo(void);
	~MenuQuickCargo(void);

	// Methods
	void notifyItemClicked();
};

