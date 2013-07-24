#pragma once
#include "MenuQuickItem.h"


class MenuQuickSystem : public MenuQuickItem
{
public:
	// Constructor - Destructor
	MenuQuickSystem(void);
	~MenuQuickSystem(void);

	// Methods
	void notifyItemClicked();
};

