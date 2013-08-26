#include "StationModel.h"
#include "Tools.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationModel::StationModel(KeyValueFile* p_config) : MapObjectModel(p_config)
{
	this->loadFromConfig(p_config);
}

StationModel::~StationModel(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void StationModel::loadFromConfig( KeyValueFile* p_config )
{
	DestructableData::loadFromConfig(p_config);
	this->loadNpcDataFromConfig(p_config);
}
