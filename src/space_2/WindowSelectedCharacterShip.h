#pragma once
#include "WindowSelected.h"
#include "CharacterShip.h"

// Define
#define LIFEBAR_COUNT			3

class WindowSelectedCharacterShip : public WindowSelected
{
public:
	// Constructor - Destructor
	WindowSelectedCharacterShip(CharacterShip* p_ship);
	~WindowSelectedCharacterShip(void);

	// Getters - Setters
	CharacterShip* getCharacterShip();
	void setCharacterShip(CharacterShip* p_ship);

	// Methods
	void notifyPositionChanged();
	void notifyCharacterShipChanged();
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void drawContent();


private:
	// Attributs
	CharacterShip* mCharacterShip;

	TextBox mTBName;
	TextBox mTBNameValue;
	TextBox mTBLevel;
	TextBox mTBLevelValue;
	TextBox mTBShield;
	TextBox mTBArmor;
	TextBox mTBStructure;
	LifeBar *mLifeBars[LIFEBAR_COUNT];
};

