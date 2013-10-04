#pragma once
#include "Window.h"
#include "ContainerableView.h"


class WindowCargoStation : public Window
{
public:
	// Constructor - Destructor
	WindowCargoStation(std::string p_title);
	~WindowCargoStation(void);

	// Getters - Setters
	ContainerableView* getContainerableView();

	// Methods
	void notifyPositionChanged();
	void notifyContainerableViewChanged();
	void update();
	void update(sf::Event p_event);
	void drawContent();


private:
	// Attributs
	ContainerableView *mContainerView;
};

