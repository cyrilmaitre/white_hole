#pragma once
#include "MenuQuickItem.h"


class MenuQuickQuest : public MenuQuickItem
{
public:
	// Constructor - Destructor
	MenuQuickQuest(void);
	~MenuQuickQuest(void);

	// Methods
	void notifyItemClicked();
};

