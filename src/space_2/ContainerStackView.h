#pragma once
#include "Focusable.h"
#include "Button.h"
#include "PopupBubble.h"

// Define
#define CONTAINERSTACKVIEW_WIDTH						36
#define CONTAINERSTACKVIEW_HEIGHT						36
#define CONTAINERSTACKVIEW_PADDING						5

class ContainerStack;

class ContainerStackView : public Focusable
{
public:
	// Constructor
	ContainerStackView(ContainerStack* p_stack);
	~ContainerStackView(void);
	void deleteIcon();

	// Getters - Setters
	ContainerStack* getContainerStack();
	void setContainerStack(ContainerStack* p_stack);

	sf::Sprite* getIcon();

	// Methods
	void update();
	void updatePosition(double newX, double newY);
	void notifyPositionChanged();
	void notifyItemStackChanged();
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	ContainerStack* mContainerStack;
	sf::RectangleShape mBackground;
	sf::RectangleShape mBackgroundIcon;
	sf::RectangleShape mOverlayStackSize;
	sf::Sprite* mIcon;
	sf::Text mStackSize;
	PopupBubble* mPubItemStack;
};

