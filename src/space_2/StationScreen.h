#pragma once
#include "Resource.h"
#include "Station.h"
#include "Button.h"
#include "FieldSet.h"
#include "StationScreenLeftMenu.h"


class StationScreen
{
public:
	// Constructor - Destructor
	StationScreen(Character* p_character);
	~StationScreen(void);

	// Getters - Setters
	Character* getCharacter();
	void setCharacter(Character* p_character);

	Station* getStation();
	void setStation(Station* p_station);

	// Methods
	void launchBegin();
	void launchEnd();
	void launch(Station* p_station);
	void update();
	void updatePosition();
	void updateBackgroundScale();
	void update(sf::Event p_event);
	void draw();
	void notifyAppSizeChanged();
	void notifyStationChanged();
	void notifyCharacterChanged();


private:
	// Attributs
	Character* mCharacter;
	Station* mStation;
	sf::Event mEvent;

	sf::Sprite mBackground;
	StationScreenLeftMenu* mLeftMenu;
};

