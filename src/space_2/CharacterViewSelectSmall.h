#pragma once
#include "Character.h"
#include "Listable.h"
#include "TextBox.h"
#include "Image.h"

// Define
#define CHARACTERVIEW_SELECTSMALL_WIDTH		350

class CharacterViewSelectSmall: public Listable
{
public:
	// Constructor - Destructor
	CharacterViewSelectSmall(Character *p_character);
	~CharacterViewSelectSmall(void);

	// Getters - Setters
	Character* getCharacter();
	void setCharacter(Character *p_character);

	// Methods
	void notifyCharacterChanged();
	void notifyPositionChanged();
	void update(sf::Event p_event);
	void updateText();
	void draw();


private:
	// Attributs
	Character *mCharacter;
	Image mAvatar;
	TextBox *mTBLabelName;
	TextBox *mTBTextName;
	TextBox *mTBLabelLevel;
	TextBox *mTBTextLevel;
};

