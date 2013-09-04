#pragma once
#include "Resource.h"
#include "Station.h"
#include "Button.h"


class StationScreen
{
public:
	// Constructor - Destructor
	StationScreen(void);
	~StationScreen(void);

	// Getters - Setters
	Station* getStation();
	void setStation(Station* p_station);

	// Methods
	void launch(Station* p_station);
	void update();
	void updatePosition();
	void updateBackgroundScale();
	void update(sf::Event p_event);
	void draw();
	void notifyAppSizeChanged();
	void notifyStationChanged();


private:
	// Attributs
	Station* mStation;
	sf::Event mEvent;

	sf::Sprite mBackground;
	Button mButtonUndock;
};

