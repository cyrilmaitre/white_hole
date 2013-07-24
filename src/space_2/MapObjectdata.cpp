#include "MapObjectdata.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MapObjectData::MapObjectData(void)
{
	this->mWidth = 1;
	this->mHeight = 1;
}

MapObjectData::~MapObjectData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int MapObjectData::getWidth()
{
	return this->mWidth;
}

void MapObjectData::setWidth( int p_width )
{
	this->mWidth = p_width;
}

int MapObjectData::getHeight()
{
	return this->mHeight;
}

void MapObjectData::setHeight( int p_height )
{
	this->mHeight = p_height;
}

int MapObjectData::getRadius()
{
	return this->getWidth() > this->getHeight() ? this->getWidth() / 2 : this->getHeight() / 2;
}


//*************************************************************
// Methods
//*************************************************************
void MapObjectData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(MAPOBJECTDATA_CONFIG_WIDTH))
		this->setWidth(p_config->getInt(MAPOBJECTDATA_CONFIG_WIDTH));

	if(p_config->has(MAPOBJECTDATA_CONFIG_HEIGHT))
		this->setHeight(p_config->getInt(MAPOBJECTDATA_CONFIG_HEIGHT));
}
