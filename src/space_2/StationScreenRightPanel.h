#pragma once
#include "Resource.h"
#include "FieldSet.h"
#include "Character.h"
#include "Station.h"

class StationScreen;

class StationScreenRightPanel : public FieldSet
{
public:
	// Constructor - Destructor
	StationScreenRightPanel(Character* p_character, Station* p_station, StationScreen* p_screen);
	~StationScreenRightPanel(void);

	// Getters - Setters
	Character* getCharacter();
	void setCharacter(Character* p_character);

	Station* getStation();
	void setStation(Station* p_station);

	StationScreen* getStationScreen();
	void setStationScreen(StationScreen* p_screen);

	// Methods
	virtual void update();
	virtual void update(sf::Event p_event);
	virtual void draw();
	virtual void unload();
	virtual void notifyCharacterChanged();
	virtual void notifyStationChanged();


private:
	// Attributs
	Character* mCharacter;
	Station* mStation;
	StationScreen* mStationScreen;
};

