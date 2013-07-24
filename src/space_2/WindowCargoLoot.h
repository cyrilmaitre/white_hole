#pragma once
#include "Window.h"
#include "ContainerView.h"
#include "Wreck.h"


class WindowCargoLoot : public Window
{
public:
	// Constructor - Destructor
	WindowCargoLoot(void);
	~WindowCargoLoot(void);

	// Getters - Setters
	ContainerView* getContainerView();

	Wreck* getWreck();
	void setWreck(Wreck* p_wreck);

	// Methods
	void notifyPositionChanged();
	void notifyContainerViewChanged();
	void notifyWreckChanged();
	void update();
	void update(sf::Event p_event);
	void drawContent();


private:
	// Attributs
	ContainerView *mContainerView;
	Wreck *mWreck;

	sf::Sprite mSpriteCredit;
	TextBox mTBCredit;
	Button mButtonLootCredit;
	Button mButtonLootAll;
};

