#pragma once
#include "ContainerStackView.h"

class HangarShipWeaponView;

class ContainerStackWeaponView : public ContainerStackView
{
public:
	// Constructor - Destructor
	ContainerStackWeaponView(HangarShipWeaponView* p_view, ContainerStack* p_stack);
	~ContainerStackWeaponView(void);

	// Methods
	void updateIcon();
	void updatePub();
	void notifyItemStackChanged();


private:
	// Attributs
	HangarShipWeaponView* mHangarView;
};

