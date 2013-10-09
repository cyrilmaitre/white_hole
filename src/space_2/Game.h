#pragma once
#include "Resource.h"
#include "Camera.h"
#include "Map.h"
#include "EventManager.h"
#include "Object.h"
#include "UserInterface.h"
#include "Character.h"
#include "CharacterShip.h"
#include "LoadingGameScreen.h"
#include "UnloadingGameScreen.h"


class Game
{
public:
	// Constructor - Destructor
	Game(void);
	~Game(void);

	// Getters - Setters
	bool isRunning();
	void setRunning(bool p_running);

	Map* getMap();
	UserInterface* getUserInterface();
	Character* getCharacter();
	CharacterShip* getShipPiloted();

	// Method
	void init();
	void uninit();
	void update();
	void update(sf::Event p_event);
	void launchInit(Character* p_character);
	void launch(Character* p_character);
	void launchUninit();

	void changedShipPiloted(CharacterShip* p_ship);
	void notifyShipPilotedChanged();

	// Static
	static Game *game;


private:
	// Attributs
	bool mRunning;
	Map* mMap;
	Camera* mCamera;
	UserInterface* mUserInterface;
	Character* mCharacter;
	sf::Event mEvent;

	sf::Thread* mThreadInit;
	sf::Thread* mThreadUninit;

	LoadingGameScreen mScreenLoading;
	UnloadingGameScreen mScreenUnloading;
};

