#pragma once
#include "FieldSet.h"
#include "CharacterShip.h"
#include "TextBox.h"
#include "ContainerWeaponStackView.h"
#include "Image.h"
#include "PopupBubble.h"


class HangarShipWeaponView : public FieldSet
{
public:
	// Constructor - Destructor
	HangarShipWeaponView(void);
	~HangarShipWeaponView(void);

	// Getters - Setters
	CharacterShip* getCharacterShip();
	void setCharacterShip(CharacterShip* p_ship);

	bool isContainerWeaponsStacksChanged();
	void setContainerWeaponsStacksChanged(bool p_value);

	// Methods
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void draw();
	void notifySizeChanged();
	void notifyPositionChanged();
	void notifyCharacterShipChanged();
	void notifyContainerWeaponsStacksChanged();


private:
	// Attributs
	CharacterShip* mCharacterShip;
	TextBox mTBWeapon;
	Image mIconTypeAllowed;
	PopupBubble mPUBTypeAllowed;
	std::vector<ContainerWeaponStackView*> mContainerWeaponStackViews;
	bool mContainerWeaponsStacksChanged;
};

