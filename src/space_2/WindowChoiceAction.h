#pragma once


class WindowChoiceAction
{
public:
	// Constructor - Destructor
	WindowChoiceAction(void);
	~WindowChoiceAction(void);

	// Methods
	virtual void onButtonYesClicked() = 0;
	virtual void onButtonNoClicked() = 0;
};

