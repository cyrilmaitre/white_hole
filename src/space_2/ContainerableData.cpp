#include "ContainerableData.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
ContainerableData::ContainerableData(void)
{
	this->mCargoMax = 0;
}

ContainerableData::~ContainerableData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int ContainerableData::getCargoMax()
{
	return this->mCargoMax;
}

void ContainerableData::setCargoMax( int p_cargoMax )
{
	this->mCargoMax = p_cargoMax;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerableData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONTAIRABLEDATA_CONFIG_CARGOMAX))
		this->setCargoMax(p_config->getInt(CONTAIRABLEDATA_CONFIG_CARGOMAX));
}
