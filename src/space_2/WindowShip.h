#pragma once
#include "Window.h"
#include "CharacterShip.h"


class WindowShip : public Window
{
public:
	// Constructor - Destructor
	WindowShip(void);
	~WindowShip(void);

	// Getters - Setters
	CharacterShip* getCharacterShip();
	void setCharacterShip(CharacterShip* p_ship);

	// Methods
	void drawContent();
	void notifyCharacterShipChanged();


private:
	// Attributs
	CharacterShip* mCharacterShip;
};

