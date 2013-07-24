#pragma once
#include "MenuQuickItem.h"


class MenuQuickMap : public MenuQuickItem
{
public:
	// Constructor - Destructor
	MenuQuickMap(void);
	~MenuQuickMap(void);

	// Methods
	void notifyItemClicked();
};

