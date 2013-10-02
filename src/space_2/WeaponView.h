#pragma once
#include "Weapon.h"
#include "Block.h"
#include "TextBox.h"
#include "PopupBubble.h"

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

	// Methods
	void notifyWeaponChanged();
	void notifyPositionChanged();
	void notifySizeChanged();
	void update(sf::Event p_event);
	void update();
	void updateAmmoCountPosition();
	void updateAmmoCount();
	void updateAmmoIcon();
	void updateRange();
	void updateAngle();
	void draw();
	void drawReloading();


private:
	// Atrributs
	Weapon *mWeapon;
	Block mWeaponIcon;
	Block	mAmmoIcon;
	TextBox mAmmoCount;
	sf::RectangleShape mInactifShape;
	TextBox mInactifText;
	PopupBubble *mWeaponInfo;
	PopupBubble *mAmmoInfo;
	Block mRangeIcon;
	Block mAngleIcon;
	PopupBubble *mRangeInfo;
	PopupBubble *mAngleInfo;
};

