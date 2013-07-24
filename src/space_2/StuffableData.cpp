#include "StuffableData.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
StuffableData::StuffableData(void)
{
	this->mStuffSlotMax = 0;
}

StuffableData::~StuffableData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int StuffableData::getStuffSlotMax()
{
	return this->mStuffSlotMax;
}

void StuffableData::setStuffSlotMax( int p_slotMax )
{
	if(p_slotMax < 0)
		p_slotMax = 0;

	this->mStuffSlotMax = p_slotMax;
}


//*************************************************************
// Methods
//*************************************************************
void StuffableData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(STUFFABLEDATA_CONFIG_STUFFSLOTMAX))
		this->setStuffSlotMax(p_config->getInt(STUFFABLEDATA_CONFIG_STUFFSLOTMAX));
}

void StuffableData::loadFromStuffableData( StuffableData* p_object )
{
	this->setStuffSlotMax(p_object->getStuffSlotMax());
}
