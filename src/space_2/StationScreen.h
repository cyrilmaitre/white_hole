#pragma once
#include "Resource.h"
#include "Station.h"
#include "Button.h"
#include "FieldSet.h"
#include "StationScreenLeftMenu.h"
#include "StationScreenRightPanel.h"
#include "StationScreenMarket.h"
#include "StationScreenHangar.h"


class StationScreen
{
public:
	// Constructor - Destructor
	StationScreen(Character* p_character);
	~StationScreen(void);

	// Getters - Setters
	int getWidth();
	int getHeight();

	Character* getCharacter();
	void setCharacter(Character* p_character);

	Station* getStation();
	void setStation(Station* p_station);

	StationScreenLeftMenu* getLeftMenu();

	StationScreenRightPanel* getRightPanel();
	void setRightPanel(StationScreenRightPanel* p_panel);

	// Methods
	void undock();
	void unloadPanel();
	void loadPanelHangar();
	void loadPanelMarket();
	void loadPanelCraft();
	void launchBegin();
	void launchEnd();
	void launch(Station* p_station);
	void update();
	void updatePosition();
	void updateBackgroundScale();
	void updateRightPanelPositon();
	void updateRightPanelSize();
	void updateRightPanelCharacter();
	void updateRightPanelStation();
	void update(sf::Event p_event);
	void draw();
	void notifyAppSizeChanged();
	void notifyStationChanged();
	void notifyCharacterChanged();
	void notifyRightPanelChanged();


private:
	// Attributs
	Character* mCharacter;
	Station* mStation;
	sf::Event mEvent;

	sf::Sprite mBackground;
	StationScreenLeftMenu* mLeftMenu;
	StationScreenRightPanel* mRightPanel;

	StationScreenMarket* mPanelMarket;
	StationScreenHangar* mPanelHangar;
};

