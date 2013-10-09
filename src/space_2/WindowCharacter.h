#pragma once
#include "Window.h"
#include "Character.h"


class WindowCharacter : public Window
{
public:
	// Constructor - Destructor
	WindowCharacter(void);
	~WindowCharacter(void);

	// Getters - Setters
	Character* getCharacter();
	void setCharacter(Character* p_character);

	// Methods
	void drawContent();
	void notifyCharacterChanged();


private:
	// Attributs
	Character* mCharacter;
};

