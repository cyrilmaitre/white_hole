#pragma once
#include "StationScreenRightPanel.h"
#include "ListSelectableGroup.h"
#include "HangarShipListView.h"
#include "HangarSlotManagementView.h"
#include "HangarShipAddView.h"
#include "HangarShipDetailView.h"


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
	void notifyCharacterChanged();
	void notifyCharacterShipSelectedChanged();


private:
	// Attributs
	ListSelectableGroup mShipList;
	HangarSlotManagementView mSlotManagementView;
	HangarShipAddView mShipAddView;
	HangarShipDetailView mShipDetailView;
};

