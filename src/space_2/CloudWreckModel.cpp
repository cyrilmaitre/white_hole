#include "CloudWreckModel.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_OPACITY		"opacity"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CloudWreckModel::CloudWreckModel( KeyValueFile* p_config ) : MapObjectModel(p_config)
{
	this->loadFromConfig(p_config);
}

CloudWreckModel::~CloudWreckModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
MapObject::MapObjectOpacity CloudWreckModel::getOpacity()
{
	return this->mOpacity;
}

void CloudWreckModel::setOpacity( MapObject::MapObjectOpacity p_opacity )
{
	this->mOpacity = p_opacity;
}


//*************************************************************
// Methods
//*************************************************************
void CloudWreckModel::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_OPACITY))
		this->setOpacity((MapObject::MapObjectOpacity)p_config->getInt(CONFIG_OPACITY));
}
