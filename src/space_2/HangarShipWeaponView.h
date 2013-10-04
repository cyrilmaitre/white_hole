#pragma once
#include "FieldSet.h"
#include "CharacterShip.h"
#include "TextBox.h"
#include "ContainerStackWeaponView.h"
#include "ContainerItemAmmoView.h"
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

	bool isContainerAmmosItemsChanged();
	void setContainerAmmosItemsChanged(bool p_value);

	// Methods
	void update();
	void updateCharacterShipWeapons();
	void updateCharacterShipWeaponAmmos();
	void updateContainerAmmosItems();
	void update(sf::Event p_event);
	void updatePosition();
	void draw();
	void notifySizeChanged();
	void notifyPositionChanged();
	void notifyCharacterShipChanged();
	void notifyContainerWeaponsStacksChanged();
	void notifyContainerAmmosItemChanged();


private:
	// Attributs
	CharacterShip* mCharacterShip;
	TextBox mTBWeapon;
	TextBox mTBAmmo;
	Image mIconTypeAllowed;
	PopupBubble mPUBTypeAllowed;

	std::vector<ContainerStackWeaponView*> mContainerWeaponStackViews;
	bool mContainerWeaponsStacksChanged;

	std::vector<ContainerItemAmmoView*> mContainerAmmosItemViews;
	bool mContainerAmmosItemsChanged;
};

