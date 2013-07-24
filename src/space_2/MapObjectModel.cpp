#include "MapObjectModel.h"
#include "Tools.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_ID				"id"
#define CONFIG_HITBOX_WIDTH		"hitbox_width"
#define CONFIG_HITBOX_HEIGHT	"hitbox_height"
#define CONFIG_SCALE_MIN		"scale_min"
#define CONFIG_SCALE_MAX		"scale_max"
#define CONFIG_SPRITE			"sprite"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MapObjectModel::MapObjectModel( KeyValueFile* p_config )
{
	this->loadFromConfig(p_config);
}

MapObjectModel::~MapObjectModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long MapObjectModel::getId()
{
	return this->mId;
}

void MapObjectModel::setId( long p_id )
{
	this->mId = p_id;
}

int MapObjectModel::getHitBoxWidth()
{
	return this->mHitBoxWidth;
}

void MapObjectModel::setHitBoxWidth( int p_width )
{
	this->mHitBoxWidth = p_width;
}

int MapObjectModel::getHitBoxHeight()
{
	return this->mHitBoxHeight;
}

void MapObjectModel::setHitBoxHeight( int p_height )
{
	this->mHitBoxHeight = p_height;
}

float MapObjectModel::getScaleMin()
{
	return this->mScaleMin;
}

void MapObjectModel::setScaleMin( float p_min )
{
	this->mScaleMin = p_min;
}

float MapObjectModel::getScaleMax()
{
	return this->mScaleMax;
}

void MapObjectModel::setScaleMax( float p_max )
{
	this->mScaleMax = p_max;
}

std::string MapObjectModel::getSprite()
{
	return this->mSprite;
}

void MapObjectModel::setSprite( std::string p_sprite )
{
	this->mSprite = p_sprite;
}


//*************************************************************
// Methods
//*************************************************************
void MapObjectModel::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_ID))
		this->setId(p_config->getLong(CONFIG_ID));

	if(p_config->has(CONFIG_HITBOX_WIDTH))
		this->setHitBoxWidth(p_config->getInt(CONFIG_HITBOX_WIDTH));

	if(p_config->has(CONFIG_HITBOX_HEIGHT))
		this->setHitBoxHeight(p_config->getInt(CONFIG_HITBOX_HEIGHT));

	if(p_config->has(CONFIG_SCALE_MIN))
		this->setScaleMin(p_config->getFloat(CONFIG_SCALE_MIN));

	if(p_config->has(CONFIG_SCALE_MAX))
		this->setScaleMax(p_config->getFloat(CONFIG_SCALE_MAX));

	if(p_config->has(CONFIG_SPRITE))
		this->setSprite(p_config->getString(CONFIG_SPRITE));
}

float MapObjectModel::getRandomScale()
{
	float returnValue = Tools::random(this->getScaleMin(), this->getScaleMax(), 2);
	return returnValue;
}



