#pragma once
#include "MenuQuickItem.h"


class MenuQuickCharacter : public MenuQuickItem
{
public:
	// Constructor - Destructor
	MenuQuickCharacter(void);
	~MenuQuickCharacter(void);

	// Methodes
	void notifyItemClicked();
};

