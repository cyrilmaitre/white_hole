#pragma once
#include "CharacterShip.h"
#include "FieldSet.h"
#include "Image.h"
#include "TextBox.h"
#include "Button.h"


class HangarShipDetailView : public FieldSet
{
public:
	// Constructor - Desturctor
	HangarShipDetailView(void);
	~HangarShipDetailView(void);

	// Getters - Setters
	CharacterShip* getCharacterShip();
	void setCharacterShip(CharacterShip* p_ship);

	// Methods
	void update();
	void update(sf::Event p_event);
	void updatePositon();
	void draw();
	void notifyPositionChanged();
	void notifyCharacterShipChanged();


private:
	// Attributs
	CharacterShip* mCharacterShip;
	Image mIcon;
	TextBox mTBName;
	TextBox mTBType;
	TextBox mTBLevel;
};

