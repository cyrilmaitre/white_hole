#include "UpgradableData.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
UpgradableData::UpgradableData(void)
{
	this->mUpgradeSlotMax = 0;
}

UpgradableData::~UpgradableData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int UpgradableData::getUpgradeSlotMax()
{
	return this->mUpgradeSlotMax;
}

void UpgradableData::setUpgradeSlotMax( int p_slotMax )
{
	if(p_slotMax < 0)
		p_slotMax = 0;

	this->mUpgradeSlotMax = p_slotMax;
}


//*************************************************************
// Methods
//*************************************************************
void UpgradableData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(UPGRADBLEDATA_CONFIG_UPGRADESLOTMAX))
		this->setUpgradeSlotMax(p_config->getInt(UPGRADBLEDATA_CONFIG_UPGRADESLOTMAX));
}

void UpgradableData::loadFromUpgradableData( UpgradableData* p_object )
{
	this->setUpgradeSlotMax(p_object->getUpgradeSlotMax());
}
