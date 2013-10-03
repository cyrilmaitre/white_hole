#pragma once
#include "Resource.h"
#include "Camera.h"
#include "Map.h"
#include "EventManager.h"
#include "Object.h"
#include "UserInterface.h"
#include "Character.h"
#include "CharacterShip.h"


class Game
{
public:
	// Constructor - Destructor
	Game(void);
	~Game(void);

	// Getters - Setters
	Map* getMap();
	void setMap(Map* p_myMap);

	UserInterface* getUserInterface();
	Character* getCharacter();
	CharacterShip* getShipPiloted();

	// Method
	void update();
	void update(sf::Event p_event);
	void launchInit(Character* p_character);
	void launch(Character* p_character);
	void launchUninit();
	void launchTest();
	void quitGame();

	void changedShipPiloted(CharacterShip* p_ship);
	void notifyShipPilotedChanged();

	// Static
	static Game *game;


private:
	// Attributs
	Map* mMap;
	Camera* mCamera;
	UserInterface* mUserInterface;
	Character* mCharacter;
	sf::Event mEvent;
};

