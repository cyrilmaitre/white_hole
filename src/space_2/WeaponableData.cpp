#include "WeaponableData.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WeaponableData::WeaponableData(void)
{
	this->mWeaponSlotMax = 0;
}

WeaponableData::~WeaponableData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int WeaponableData::getWeaponSlotMax()
{
	return this->mWeaponSlotMax;
}

void WeaponableData::setWeaponSlotMax( int p_slotMax )
{
	if(p_slotMax < 0)
		p_slotMax = 0;

	this->mWeaponSlotMax = p_slotMax;
}


//*************************************************************
// Methods
//*************************************************************
void WeaponableData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(WEAPONABLEDATA_CONFIG_WEAPONSLOTMAX))
		this->setWeaponSlotMax(p_config->getInt(WEAPONABLEDATA_CONFIG_WEAPONSLOTMAX));
}

void WeaponableData::loadFromWeaponableData( WeaponableData* p_object )
{
	this->setWeaponSlotMax(p_object->getWeaponSlotMax());
}
