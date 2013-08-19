#pragma once
#include "Window.h"


class WindowChat : public Window
{
public:
	// Constructor - Destructor
	WindowChat(void);
	~WindowChat(void);

	// Methods
	void drawContent();
	void notifyPositionChanged();

private:
	TextBoxMultiLine txtbox;
};

