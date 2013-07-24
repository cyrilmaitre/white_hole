#pragma once
#include "WindowSelected.h"
#include "NpcShip.h"

// Define
#define LIFEBAR_COUNT			3

class WindowSelectedNpcShip : public WindowSelected
{
public:
	// Constructor - Destructor
	WindowSelectedNpcShip(NpcShip* p_ship);
	~WindowSelectedNpcShip(void);

	// Getters - Setters
	NpcShip* getNpcShip();
	void setNpcShip(NpcShip* p_ship);

	// Methods
	void notifyPositionChanged();
	void notifyNpcShipChanged();
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void drawContent();


private:
	// Attributs
	NpcShip* mNpcShip;

	TextBox mTBName;
	TextBox mTBNameValue;
	TextBox mTBLevel;
	TextBox mTBLevelValue;
	TextBox mTBShield;
	TextBox mTBArmor;
	TextBox mTBStructure;
	LifeBar *mLifeBars[LIFEBAR_COUNT];
};

