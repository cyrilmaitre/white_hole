#pragma once
#include "ContainerItemView.h"

class HangarShipWeaponView;

class ContainerItemAmmoView : public ContainerItemView
{
public:
	// Constructor - Destructor
	ContainerItemAmmoView(HangarShipWeaponView* p_view, ContainerItem* p_item);
	~ContainerItemAmmoView(void);

	// Methods
	void updateIcon();
	void updatePub();
	void notifyItemChanged();


private:
	// Attributs
	HangarShipWeaponView* mHangarView;
};

