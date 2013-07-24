#pragma once
#include "Window.h"
#include "ContainerView.h"


class WindowCargo : public Window
{
public:
	// Constructor
	WindowCargo(void);
	~WindowCargo(void);

	// Getters - Setters
	ContainerView* getContainerView();

	// Methods
	void notifyPositionChanged();
	void notifyContainerViewChanged();
	void update();
	void update(sf::Event p_event);
	void drawContent();


private:
	// Attributs
	ContainerView *mContainerView;
};

