#pragma once
#include "Window.h"
#include "ContainerableView.h"


class WindowCargo : public Window
{
public:
	// Constructor
	WindowCargo(void);
	~WindowCargo(void);

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
	ContainerableView *mContainerableView;
};

