#include "RotableData.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_ROTATIONVELOCITY				"rotation_velocity"
#define CONFIG_ROTATIONVELOCITYINSTANT		"rotation_velocityinstant"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
RotableData::RotableData(void)
{
	this->mRotationVelocity = 0;
	this->mRotationVelocityInstant = false;
}

RotableData::~RotableData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
float RotableData::getRotationVelocity()
{
	return this->mRotationVelocity;
}

void RotableData::setRotationVelocity( float p_velocity )
{
	this->mRotationVelocity = p_velocity;
}

bool RotableData::isRotationVelocityInstant()
{
	return this->mRotationVelocityInstant;
}

void RotableData::setRotationVelocityInstant( bool p_instant )
{
	this->mRotationVelocityInstant = p_instant;
}


//*************************************************************
// Methods
//*************************************************************
void RotableData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_ROTATIONVELOCITY))
		this->setRotationVelocity(p_config->getFloat(CONFIG_ROTATIONVELOCITY));

	if(p_config->has(CONFIG_ROTATIONVELOCITYINSTANT))
		this->setRotationVelocityInstant(p_config->getBool(CONFIG_ROTATIONVELOCITYINSTANT));
}

void RotableData::loadFromRotableData( RotableData* p_data )
{
	this->setRotationVelocity(p_data->getRotationVelocity());
	this->setRotationVelocityInstant(p_data->isRotationVelocityInstant());
}


