#pragma once
#include "Window.h"
#include "Button.h"


class WindowSystem : public Window
{
public:
	// Constructor - Destructor
	WindowSystem(void);
	~WindowSystem(void);

	// Methods
	void updatePosition();
	void update(sf::Event p_event);
	void drawContent();
	void notifyPositionChanged();


private:
	// Attributs
	Button mButtonOption;
	Button mButtonLogout;
	Button mButtonQuit;
};

