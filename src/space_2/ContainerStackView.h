#pragma once
#include "ContainerView.h"
#include "ContainerStack.h"

// Define
#define CONTAINERSTACKVIEW_PADDING		5

class ContainerStackView : public ContainerView
{
public:
	// Constructor
	ContainerStackView(ContainerStack* p_stack = NULL);
	~ContainerStackView(void);
	
	// Getters - Setters
	ContainerStack* getContainerStack();
	void setContainerStack(ContainerStack* p_stack);

	bool isDisplayStackSize();
	void setDisplayStackSize(bool p_value);

	// Methods
	void update();
	void updateBackgroundColor();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	virtual void notifyItemStackChanged();


protected:
	// Attributs
	ContainerStack* mContainerStack;

	sf::RectangleShape mOverlayStackSize;
	sf::Text mStackSize;
	bool mDisplayStackSize;
};

