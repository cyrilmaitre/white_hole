#pragma once
#include "MenuQuickItem.h"


class MenuQuickJukebox : public MenuQuickItem
{
public:
	// Constructor - Destructor
	MenuQuickJukebox(void);
	~MenuQuickJukebox(void);

	// Methods
	void notifyItemClicked();
};

