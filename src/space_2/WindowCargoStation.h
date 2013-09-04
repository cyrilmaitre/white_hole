#pragma once
#include "Window.h"
#include "ContainerView.h"


class WindowCargoStation : public Window
{
public:
	// Constructor - Destructor
	WindowCargoStation(std::string p_title);
	~WindowCargoStation(void);

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

