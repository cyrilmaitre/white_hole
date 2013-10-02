#pragma once
#include "FieldSet.h"
#include "CharacterShip.h"
#include "TextBox.h"
#include "ContainerWeaponStackView.h"


class HangarShipWeaponView : public FieldSet
{
public:
	// Constructor - Destructor
	HangarShipWeaponView(void);
	~HangarShipWeaponView(void);

	// Getters - Setters
	CharacterShip* getCharacterShip();
	void setCharacterShip(CharacterShip* p_ship);

	bool isWeaponsChanged();
	void setWeaponsChanged(bool p_value);

	// Methods
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void draw();
	void notifySizeChanged();
	void notifyPositionChanged();
	void notifyCharacterShipChanged();
	void notifyWeaponsChanged();


private:
	// Attributs
	CharacterShip* mCharacterShip;
	TextBox mTBWeapon;
	std::vector<ContainerWeaponStackView*> mWeaponsView;
	bool mWeaponsChanged;
	bool mIgnoreWeaponsChanged;
};

