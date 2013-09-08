#pragma once


class WindowChoiceAction
{
public:
	// Constructor - Destructor
	WindowChoiceAction(void);
	~WindowChoiceAction(void);

	// Methods
	virtual void onButtonTrueClicked() = 0;
	virtual void onButtonFalseClicked() = 0;
};

