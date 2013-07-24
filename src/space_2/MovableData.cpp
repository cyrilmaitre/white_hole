#include "MovableData.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_VELOCITYMAX				"velocity"
#define CONFIG_QUICKENING				"quickening"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MovableData::MovableData(void)
{
	this->mVelocityMax = 0;
	this->mQuickening = 0;
}

MovableData::~MovableData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
float MovableData::getVelocityMax()
{
	return this->mVelocityMax;
}

void MovableData::setVelocityMax( float p_velocityMax )
{
	// Check param
	if(p_velocityMax < 0)
		p_velocityMax = 0;

	// Set
	this->mVelocityMax = p_velocityMax;
}

float MovableData::getQuickening()
{
	return this->mQuickening;
}

void MovableData::setQuickening( float p_quickening )
{
	this->mQuickening = p_quickening;
}


//*************************************************************
// Methods
//*************************************************************
void MovableData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_VELOCITYMAX))
		this->setVelocityMax(p_config->getFloat(CONFIG_VELOCITYMAX));

	if(p_config->has(CONFIG_QUICKENING))
		this->setQuickening(p_config->getFloat(CONFIG_QUICKENING));
}

void MovableData::loadFromMovableData( MovableData* p_object )
{
	this->setVelocityMax(p_object->getVelocityMax());
	this->setQuickening(p_object->getQuickening());
}

