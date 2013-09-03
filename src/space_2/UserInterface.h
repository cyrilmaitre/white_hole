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
#include "WindowCargoLoot.h"
#include "ExperienceBar.h"
#include "WindowMap.h"
#include "WindowSelectedEntity.h"

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
	WindowSelectedEntity* getWindowSelectedEntity();
	WindowCargo* getWindowCargo();
	WindowCargoLoot* getWindowCargoLoot();
	WindowMap* getWindowMap();

	WindowSelected* getWindowSelected();
	void setWindowSelected(WindowSelected* p_window);

	ExperienceBar* getXpBarCharacter();
	sf::Vector2i getInterfaceBottom();

	// Methode	
	void update(sf::Event p_event);
	void update();
	void updatePosition();
	void updateWeaponPosition();
	void updateWindowDynamics();
	void draw();

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
	WindowSelectedEntity* mWindowSelectedEntity;

	std::vector<Window*> mWindowDynamics;
	WindowCharacter *mWindowCharacter;
	WindowCargo *mWindowCargo;
	WindowCargoLoot *mWindowCargoLoot;
	WindowMap *mWindowMap;
	WindowJukebox *mWindowJukebox;

	// Interface bottom
	MenuQuick mMenuQuick;
	sf::Sprite mInterfaceBottom;
	std::vector<WeaponView*> mWeaponViews;
	ExperienceBar mXpBarCharacter;

	// Methods 
	void moveWindowDynamicToBegin(int p_index);
};

