#pragma once
#include "FieldSet.h"
#include "CharacterShip.h"
#include "TextBox.h"


class HangarShipWeaponView : public FieldSet
{
public:
	// Constructor - Destructor
	HangarShipWeaponView(void);
	~HangarShipWeaponView(void);

	// Getters - Setters
	CharacterShip* getCharacterShip();
	void setCharacterShip(CharacterShip* p_ship);

	// Methods
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void draw();
	void notifySizeChanged();
	void notifyPositionChanged();
	void notifyCharacterShipChanged();


private:
	// Attributs
	CharacterShip* mCharacterShip;
	TextBox mTBWeapon;
};

