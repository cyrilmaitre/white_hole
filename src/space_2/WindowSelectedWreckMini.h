#pragma once
#include "WindowSelected.h"
#include "WreckMini.h"
#include "Button.h"

// Define
#define LIFEBAR_COUNT			3

class WindowSelectedWreckMini : public WindowSelected
{
public:
	// Constructor - Destructor
	WindowSelectedWreckMini(WreckMini* p_wreck);
	~WindowSelectedWreckMini(void);

	// Getters - Setters
	WreckMini* getWreckMini();
	void setWreckMini(WreckMini* p_wreck);

	// Methods
	void recycleWreckMini();
	void notifyPositionChanged();
	void notifyWreckMiniChanged();
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void drawContent();


private:
	// Attributs
	WreckMini* mWreckMini;

	TextBox mTBName;
	TextBox mTBNameValue;
	TextBox mTBShield;
	TextBox mTBArmor;
	TextBox mTBStructure;
	Button mButtonRecycle;
	LifeBar *mLifeBars[LIFEBAR_COUNT];
};

