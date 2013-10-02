#pragma once
#include "ContainerStackView.h"

class HangarShipWeaponView;


class ContainerWeaponStackView : public ContainerStackView
{
public:
	// Constructor - Destructor
	ContainerWeaponStackView(HangarShipWeaponView* p_view, ContainerStack* p_stack);
	~ContainerWeaponStackView(void);

	// Methods
	void notifyItemStackChanged();


private:
	// Attributs
	HangarShipWeaponView* mHangarView;
};

