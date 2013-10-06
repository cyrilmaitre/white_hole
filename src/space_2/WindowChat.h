#pragma once
#include "Window.h"
#define MAX_CHAT_LINES 100

class WindowChat : public Window
{
public:
	// Constructor - Destructor
	WindowChat(void);
	~WindowChat(void);

	// Methods
	void drawContent();
	void update(sf::Event p_event);
	void notifyPositionChanged();
	void pushChat(std::string p_string);
	void clearChat();

private:
	TextBoxMultiLine			txtbox;
	TextBoxMultiLine			txtboxUL;
	TextField					txtfield;
	std::deque<std::string>		chatLines;
};

