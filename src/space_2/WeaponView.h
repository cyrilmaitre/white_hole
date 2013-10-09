#pragma once
#include "Weapon.h"
#include "Block.h"
#include "TextBox.h"
#include "PopupBubble.h"
#include "ContainerItemAmmoView.h"

// Define
#define WEAPONVIEW_WIDTH						86	
#define WEAPONVIEW_HEIGHT						88

class WeaponView : public Block
{
public:
	// Constructor - Destructor
	WeaponView(	Weapon *p_weapon = NULL);
	~WeaponView(void);

	// Getters - Setters
	Weapon *getWeapon();
	void setWeapon(Weapon *p_weapon);

	bool isAmmoContainerChanged();
	void setAmmoContainerChanged(bool p_changed);

	// Methods
	void update(sf::Event p_event);
	void update();
	void updatePosition();
	void updateWeaponInfo();
	void updateAmmoCountPosition();
	void updateAmmoCount();
	void updateAmmoContainer();
	void updateRange();
	void updateAngle();

	void draw();
	void drawReloading();

	void notifyWeaponChanged();
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyAmmoContainerChanged();


private:
	// Atrributs
	Weapon *mWeapon;

	sf::RectangleShape mInactifShape;
	TextBox mInactifText;

	Block mWeaponIcon;
	PopupBubble* mWeaponInfo;

	ContainerItemAmmoView* mAmmoContainer;
	bool mAmmoContainerChanged;
	TextBox mAmmoCount;
	
	Block mRangeIcon;
	Block mAngleIcon;

	PopupBubble* mRangeInfo;
	PopupBubble* mAngleInfo;
};

