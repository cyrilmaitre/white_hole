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
#include "WindowPopup.h"
#include "FieldSet.h"
#include "Clock.h"
#include "ImageGIF.h"
#include "WindowShip.h"

// Define
#define INTERFACEBOTTOM_WIDTH				775
#define INTERFACEBOTTOM_HEIGHT				167

class UserInterface
{
public:
	// Constructor - Destructor 
	UserInterface(Character* p_character);
	~UserInterface(void);

	// Getters - Setters
	Character* getCharacter();
	void setCharacter(Character* p_character);

	bool isSavingGifVisible();
	void setSavingGifVisible(bool p_value);

	WindowShipSmall* getWindowShipSmall();
	WindowCharacter* getWindowCharacter();
	WindowShip* getWindowShip();
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

	WindowCargoStation* getWindowCargoStationShip();
	int getWindowCargoStationBankCount();
	WindowCargoStation* getWindowCargoStationBank(int p_index);

	WindowSelected* getWindowSelected();
	void setWindowSelected(WindowSelected* p_window);

	StationScreen* getStationScreen();
	ExperienceBar* getXpBarCharacter();
	ExperienceBar* getXpBarCharacterShip();
	sf::Vector2i getInterfaceBottom();

	// Methode	
	void addWindowPopup(WindowPopup* p_window);
	void removeWindowPopup(WindowPopup* p_window);

	void update(sf::Event p_event);
	void updateInStation(sf::Event p_event);
	void updateInGame(sf::Event p_event);

	void update();
	void updateInStation();
	void updateInGame();

	void draw();
	void drawInStation();
	void drawInGame();

	void updateDashboard();
	void updatePosition();
	void updateWeaponPosition();
	void handleScreenAppResized();
	void notifyWeaponViewChanged();
	void notifyCharacterChanged();

	// Static
	static UserInterface* mUserInterface;


private:
	// Attributs
	Character* mCharacter;

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
	WindowShip* mWindowShip;
	ContainerableView* mCargoShipView;
	WindowCargo *mWindowCargo;
	WindowCargoLoot *mWindowCargoLoot;
	WindowMap *mWindowMap;
	WindowJukebox *mWindowJukebox;

	std::vector<Window*> mWindowDynamicsStation;
	WindowCargoStation* mWindowCargoStationShip;
	std::vector<WindowCargoStation*> mWindowCargoStationBanks;
	StationScreen* mStationScreen;

	std::vector<WindowPopup*> mWindowPopups;

	// Saving
	ImageGIF* mSavingGif;
	sf::Mutex mSavingGifMutex;

	// Interface bottom
	MenuQuick mMenuQuick;
	sf::Sprite mInterfaceBottom;
	FieldSet mDashboard;
	TextBox mDashboardDayLabel;
	TextBox mDashboardDay;
	TextBox mDashboardTimeLabel;
	TextBox mDashboardTime;
	TextBox mDashboardPositionLabel;
	TextBox mDashboardPosition;
	mks::Clock mDashboardClock;
	std::vector<WeaponView*> mWeaponViews;
	ExperienceBar mXpBarCharacter;
	ExperienceBar mXpBarCharacterShip;

	// Methods 
	void moveWindowDynamicToBegin(int p_index);
	void moveWindowDynamicStationToBegin(int p_index);
};

