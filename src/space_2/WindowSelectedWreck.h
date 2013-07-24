#pragma once
#include "WindowSelected.h"
#include "Wreck.h"
#include "Button.h"

// Define
#define LIFEBAR_COUNT			3

class WindowSelectedWreck : public WindowSelected
{
public:
	// Constructor - Destructor
	WindowSelectedWreck(Wreck* p_wreck);
	~WindowSelectedWreck(void);

	// Getters - Setters
	Wreck* getWreck();
	void setWreck(Wreck* p_wreck);

	// Methods
	void openWreck();
	void recycleWreck();

	void notifyOpenChanged();
	void notifyPositionChanged();
	void notifyWreckChanged();
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void drawContent();


private:
	// Attributs
	Wreck* mWreck;

	TextBox mTBName;
	TextBox mTBNameValue;
	TextBox mTBShield;
	TextBox mTBArmor;
	TextBox mTBStructure;
	Button mButtonOpen;
	Button mButtonRecycle;
	LifeBar *mLifeBars[LIFEBAR_COUNT];
};

