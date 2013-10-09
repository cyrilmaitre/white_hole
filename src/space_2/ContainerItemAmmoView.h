#pragma once
#include "ContainerItemView.h"

class HangarShipWeaponView;
class WeaponView;

class ContainerItemAmmoView : public ContainerItemView
{
public:
	// Constructor - Destructor
	ContainerItemAmmoView(HangarShipWeaponView* p_view, ContainerItem* p_item);
	ContainerItemAmmoView(WeaponView* p_view, ContainerItem* p_item);
	void init();
	~ContainerItemAmmoView(void);

	// Methods
	void updateIcon();
	void updatePub();
	void notifyItemChanged();


private:
	// Attributs
	HangarShipWeaponView* mHangarView;
	WeaponView* mWeaponView;
};

