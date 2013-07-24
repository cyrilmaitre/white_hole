#pragma once
#include "Window.h"
#include "CharacterShip.h"
#include "LifeBar.h"

// Define
#define LIFEBAR_COUNT		3

class WindowShipSmall: public Window
{
public:
	// Constructor - Destructor
	WindowShipSmall(void);
	~WindowShipSmall(void);

	// Getters - Setters
	CharacterShip* getCharacterShip();
	void setCharacterShip(CharacterShip *p_ship);

	// Methods
	void notifyPositionChanged();
	void notifyCharacterShipChanged();
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void drawContent();


private:
	// Attributs
	CharacterShip *mCharacterShip;
	TextBox *mTBShieldLabel;
	TextBox *mTBArmorLabel;
	TextBox *mTBStructureLabel;
	LifeBar *mLifeBars[LIFEBAR_COUNT];
};

