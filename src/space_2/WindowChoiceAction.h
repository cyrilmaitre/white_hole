#pragma once
#include "Resource.h"


class WindowChoiceAction
{
public:
	// Constructor - Destructor
	WindowChoiceAction(void);
	~WindowChoiceAction(void);

	// Methods
	virtual void onButtonTrueClicked(std::string p_actionCommand) = 0;
	virtual void onButtonFalseClicked(std::string p_actionCommand) = 0;
};

