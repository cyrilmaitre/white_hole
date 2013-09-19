#pragma once
#include "TextBox.h"

class DropDownable : public TextBox
{
public:
	// Constructor - Destructor
	DropDownable(void);
	~DropDownable(void);

	// Methods
	void notifySelectedChanged();
};

