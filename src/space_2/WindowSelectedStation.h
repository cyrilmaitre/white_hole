#pragma once
#include "WindowSelected.h"
#include "Station.h"
#include "Button.h"

// Define
#define LIFEBAR_COUNT			3

class WindowSelectedStation : public WindowSelected
{
public:
	// Constructor - Destructor
	WindowSelectedStation(Station* p_station);
	~WindowSelectedStation(void);

	// Getters - Setters
	Station* getStation();
	void setStation(Station* p_station);

	// Methods
	void dock();
	void notifyPositionChanged();
	void notifyStationChanged();
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void drawContent();


private:
	// Attibuts
	Station* mStation;

	TextBox mTBName;
	TextBox mTBNameValue;
	TextBox mTBLevel;
	TextBox mTBLevelValue;
	TextBox mTBShield;
	TextBox mTBArmor;
	TextBox mTBStructure;
	Button mButtoDock;
	LifeBar *mLifeBars[LIFEBAR_COUNT];
};

