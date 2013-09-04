#pragma once
#include "WindowCharacter.h"
#include "WindowJukebox.h"
#include "WindowShipSmall.h"
#include "WindowSelected.h"
#include "WeaponView.h"
#include "MenuQuick.h"
#include "WindowSelectedCharacterShip.h"
#include "WindowSelectedNpcShip.h"
#include "WindowCargo.h"
#include "WindowSelectedWreck.h"
#include "WindowSelectedWreckMini.h"
#include "WindowSelectedStation.h"
#include "WindowCargoLoot.h"
#include "ExperienceBar.h"
#include "WindowMap.h"
#include "WindowSelectedEntity.h"
#include "StationScreen.h"
#include "WindowCargoStation.h"

// Define
#define INTERFACEBOTTOM_WIDTH				775
#define INTERFACEBOTTOM_HEIGHT				167

class UserInterface
{
public:
	// Constructor - Destructor 
	UserInterface(void);
	~UserInterface(void);

	// Getters - Setters
	WindowShipSmall* getWindowShipSmall();
	WindowCharacter* getWindowCharacter();
	WindowJukebox* getWindowJukebox();
	WindowSelectedCharacterShip* getWindowSelectedCharacterShip();
	WindowSelectedNpcShip* getWindowSelectedNpcShip();
	WindowSelectedWreck* getWindowSelectedWreck();
	WindowSelectedWreckMini* getWindowSelectedWreckMini();
	WindowSelectedStation* getWindowSelectedStation();
	WindowSelectedEntity* getWindowSelectedEntity();
	WindowCargo* getWindowCargo();
	WindowCargoLoot* getWindowCargoLoot();
	WindowMap* getWindowMap();
	WindowCargoStation* getWindowStationShipCargo();

	WindowSelected* getWindowSelected();
	void setWindowSelected(WindowSelected* p_window);

	StationScreen* getStationScreen();
	ExperienceBar* getXpBarCharacter();
	sf::Vector2i getInterfaceBottom();

	// Methode	
	void update(sf::Event p_event);
	void updateWindowStatics(sf::Event p_event);
	void updateWindowDynamics(sf::Event p_event);
	void updateWindowDynamicsStation(sf::Event p_event);
	void update();
	void updateWindowStatics();
	void updateWindowDynamics();
	void updateWindowDynamicsStation();
	void updatePosition();
	void updateWeaponPosition();
	void draw();
	void drawWindowStatics();
	void drawWindowDynamics();
	void drawWindowDynamicsStation();

	void handleScreenAppResized();
	void notifyWeaponViewChanged();

	// Static
	static UserInterface* mUserInterface;


private:
	// Attributs
	WindowShipSmall *mWindowShipSmall;
	WindowSelected *mWindowSelected;
	WindowSelectedCharacterShip *mWindowSelectedCharacterShip;
	WindowSelectedNpcShip *mWindowsSelectedNpcShip;
	WindowSelectedWreck* mWindowsSelectedWreck;
	WindowSelectedWreckMini* mWindowSelectedWreckMini;
	WindowSelectedStation* mWindowSelectedStation;
	WindowSelectedEntity* mWindowSelectedEntity;

	std::vector<Window*> mWindowDynamics;
	WindowCharacter *mWindowCharacter;
	WindowCargo *mWindowCargo;
	WindowCargoLoot *mWindowCargoLoot;
	WindowMap *mWindowMap;
	WindowJukebox *mWindowJukebox;

	std::vector<Window*> mWindowDynamicsStation;
	WindowCargoStation* mWindowStationShipCargo;
	StationScreen mStationScreen;

	// Interface bottom
	MenuQuick mMenuQuick;
	sf::Sprite mInterfaceBottom;
	std::vector<WeaponView*> mWeaponViews;
	ExperienceBar mXpBarCharacter;

	// Methods 
	void moveWindowDynamicToBegin(int p_index);
	void moveWindowDynamicStationToBegin(int p_index);
};

