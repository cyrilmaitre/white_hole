#pragma once
#include "MenuQuickItem.h"


class MenuQuickChat : public MenuQuickItem
{
public:
	// Constructor - Destructor
	MenuQuickChat(void);
	~MenuQuickChat(void);

	// Methods
	void notifyItemClicked();
};


