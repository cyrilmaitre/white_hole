#pragma once
#include "StationScreenRightPanel.h"
#include "ListSelectableGroup.h"
#include "HangarShipListView.h"


class StationScreenHangar : public StationScreenRightPanel
{
public:
	// Constructor - Destructor
	StationScreenHangar(Character* p_character, Station* p_station, StationScreen* p_screen);
	~StationScreenHangar(void);

	// Methods
	void load();
	void unload();
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifySizeChanged();
	void notifyPositionChanged();


private:
	// Attributs
	ListSelectableGroup mShipList;
};

