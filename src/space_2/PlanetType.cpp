#include "PlanetType.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
PlanetType::PlanetType( KeyValueFile* p_config )
{
	this->loadFromConfig(p_config);
}

PlanetType::~PlanetType(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long PlanetType::getIdPlanetType()
{
	return this->mIdPlanetType;
}

void PlanetType::setIdPlanetType( long p_id )
{
	this->mIdPlanetType = p_id;
}

std::string PlanetType::getName()
{
	return this->mName;
}

void PlanetType::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string PlanetType::getDescription()
{
	return this->mDescription;
}

void PlanetType::setDescription( std::string p_description )
{
	this->mDescription = p_description;
}


//*************************************************************
// Methods
//*************************************************************
void PlanetType::loadFromConfig( KeyValueFile* p_config )
{
	this->setIdPlanetType(p_config->getLong(PLANETTYPE_CONFIG_ID));
	this->setName(p_config->getString(PLANETTYPE_CONFIG_NAME));
	this->setDescription(p_config->getString(PLANETTYPE_CONFIG_DESCRIPTION));
}
