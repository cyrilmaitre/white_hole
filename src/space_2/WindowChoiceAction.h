#pragma once
#include "Resource.h"
#include "WindowChoiceActionObject.h"


class WindowChoiceAction
{
public:
	// Constructor - Destructor
	WindowChoiceAction(void);
	~WindowChoiceAction(void);

	// Methods
	virtual void onButtonTrueClicked(WindowChoiceActionObject* p_object, std::string p_actionCommand) = 0;
	virtual void onButtonFalseClicked(WindowChoiceActionObject* p_object, std::string p_actionCommand) = 0;
};

