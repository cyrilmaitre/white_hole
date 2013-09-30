#include "WeaponType.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WeaponType::WeaponType(KeyValueFile* p_config)
{
	this->loadFromConfig(p_config);
}

WeaponType::~WeaponType(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long WeaponType::getIdWeaponType()
{
	return this->mIdWeaponType;
}

void WeaponType::setIdWeaponType( long p_id )
{
	this->mIdWeaponType = p_id;
}

std::string WeaponType::getName()
{
	return this->mName;
}

void WeaponType::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string WeaponType::getDescription()
{
	return this->mDescription;
}

void WeaponType::setDescription( std::string p_description )
{
	this->mDescription = p_description;
}


//*************************************************************
// Methods
//*************************************************************
void WeaponType::loadFromConfig( KeyValueFile* p_config )
{
	this->setIdWeaponType(p_config->getLong(WEAPONTYPE_CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(WEAPONTYPE_CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(WEAPONTYPE_CONFIG_DESCRIPTION)));
}
