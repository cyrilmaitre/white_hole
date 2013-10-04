#pragma once
#include "Window.h"
#include "ContainerableView.h"
#include "Wreck.h"


class WindowCargoLoot : public Window
{
public:
	// Constructor - Destructor
	WindowCargoLoot(void);
	~WindowCargoLoot(void);

	// Getters - Setters
	ContainerableView* getContainerableView();

	Wreck* getWreck();
	void setWreck(Wreck* p_wreck);

	// Methods
	void notifyPositionChanged();
	void notifyContainerableViewChanged();
	void notifyWreckChanged();
	void update();
	void update(sf::Event p_event);
	void drawContent();


private:
	// Attributs
	ContainerableView *mContainerableView;
	Wreck *mWreck;

	sf::Sprite mSpriteCredit;
	TextBox mTBCredit;
	Button mButtonLootCredit;
	Button mButtonLootAll;
};

