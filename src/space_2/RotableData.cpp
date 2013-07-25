#include "RotableData.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_ROTATIONVELOCITY				"rotation_velocity"
#define CONFIG_ROTATIONVELOCITYINSTANT		"rotation_velocityinstant"
#define CONFIG_ROTATIONINFINITE				"rotation_infinite"
#define CONFIG_ROTATIONINFINITERIGHT		"rotation_infiniteright"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
RotableData::RotableData(void)
{
	this->mRotationVelocity = 0;
	this->mRotationVelocityInstant = false;
	this->mRotationInfinite = false;
	this->mRotationInfiniteRight = true;
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

bool RotableData::isRotationInfinite()
{
	return this->mRotationInfinite;
}

void RotableData::setRotationInfinite( bool p_infinite )
{
	this->mRotationInfinite = p_infinite;
}

bool RotableData::isRotationInfiniteRight()
{
	return this->mRotationInfiniteRight;
}

void RotableData::setRotationInfiniteRight( bool p_infiniteRight )
{
	this->mRotationInfiniteRight = p_infiniteRight;
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

	if(p_config->has(CONFIG_ROTATIONINFINITE))
		this->setRotationInfinite(p_config->getBool(CONFIG_ROTATIONINFINITE));

	if(p_config->has(CONFIG_ROTATIONINFINITERIGHT))
		this->setRotationInfiniteRight(p_config->getBool(CONFIG_ROTATIONINFINITERIGHT));
}

void RotableData::loadFromRotableData( RotableData* p_data )
{
	this->setRotationVelocity(p_data->getRotationVelocity());
	this->setRotationVelocityInstant(p_data->isRotationVelocityInstant());
	this->setRotationInfinite(p_data->isRotationInfinite());
	this->setRotationInfiniteRight(p_data->isRotationInfiniteRight());
}





